/*
 * Buffer.cc
 *
 *  Created on: 2011-26-1
 *      Author: George
 */

#include "Buffer.h"

namespace n_radix_switch {

Define_Module(Buffer);

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
	delete queue;
}

void Buffer::initialize()
{
	BufferLengh = par("BufferLength").longValue();
	nvcs = par("nvcs").longValue();
	RTtreshold =  par("RTtreshold").longValue(); // TODO

	queue = new cQueue[nvcs];
	for(int vc=0; vc < nvcs; vc++) {
		char caption[20];
		queue[vc].setName("Buffer");
		Control *pCtlCredit = new Control();
		pCtlCredit->setKind(CTL_BUFFER_CREDIT);
		pCtlCredit->setVcId(vc);
		pCtlCredit->setCredits(BufferLengh - RTtreshold);
		sprintf(caption, "%d credits", BufferLengh - RTtreshold);

		pCtlCredit->setName(caption);
		send(pCtlCredit, "in_ctl");

	}

	has_shcheduled_timer = false;
	switch_clock = par("SwitchClock").doubleValue();
	timerMessage = new cMessage("timer");
}

void Buffer::finish()
{

	cancelAndDelete(timerMessage);
//	delete queue;
}

void Buffer::UpdateDisplay(int count)
{
	char buffer[20];

	cDisplayString dispStr = getDisplayString();
	sprintf(buffer, "%d flits", count);
	dispStr.setTagArg("t", 0, buffer);
	if(count == BufferLengh) {
		dispStr.setTagArg("i2", 0, "status/busy");
		dispStr.setTagArg("i", 1, "red");
	}
	setDisplayString(dispStr);
}


void Buffer::handleControlMessage(Control *pControl)
{
	Flit *pFlit;
	Control *pCtlCredit;

	int vc = pControl->getVcId();
	int port =  pControl->getPort();

	switch(pControl->getKind()) {
	case CTL_GRANT:
		pFlit = (Flit *)queue[vc].pop();
		UpdateDisplay(queue[vc].getLength());
		ASSERT(pFlit->getOutput_port() == port);

		send(pFlit, "out");

		pCtlCredit = new Control();
		pCtlCredit->setKind(CTL_BUFFER_CREDIT);
		pCtlCredit->setVcId(vc); // TODO
		pCtlCredit->setCredits(1);
		pCtlCredit->setName("1 credit");
		send(pCtlCredit, "in_ctl");
		break;

	default:
		ASSERT(0);
	}



	delete pControl;
}

void Buffer::handleTimerMessage(cMessage *msg)
{
	Flit *pFrontFlit;

	int vc = 0; // TODO

	if(queue[vc].empty()) {
		has_shcheduled_timer = false;
		return;
	} else {
		scheduleAt(simTime() + switch_clock, timerMessage);
	}

	pFrontFlit = (Flit *)queue[vc].front();

	if(pFrontFlit) {
		switch(pFrontFlit->getKind()) {
		case FLIT_HEAD: {
				currnt_channel.vc = pFrontFlit->getVcId();
				currnt_channel.port = pFrontFlit->getOutput_port();
				Control *pControl = new Control("CTL_REQ_VC");
				pControl->setKind(CTL_REQ_VC);
				pControl->setVcId(currnt_channel.vc);
				pControl->setPort(currnt_channel.port);
				send(pControl, "out_ctl");
			}
			break;
			case FLIT_PAYLOAD: {
				Control *pControl = new Control("CTL_REQ_SW");
				pControl->setKind(CTL_REQ_SW);
				pControl->setVcId(currnt_channel.vc);
				pControl->setPort(currnt_channel.port);
				send(pControl, "out_ctl");
			}
			break;
		case FLIT_TAIL: {
				Control *pControl = new Control("CTL_RELEASE_VC");
				pControl->setKind(CTL_RELEASE_VC);
				pControl->setVcId(currnt_channel.vc);
				pControl->setPort(currnt_channel.port);
				send(pControl, "out_ctl");
			}
			break;
		}
	}
}


void Buffer::handleFlitMessage(Flit *pFlit)
{
	int vc = pFlit->getVcId();

	UpdateDisplay(queue[vc].getLength());

	queue[vc].insert(pFlit);
	// EV << "queue len=" << queue[vc].getLength() << " max len=" << BufferLengh << endl;
	ASSERT(queue[vc].getLength() <= BufferLengh);

	if(!has_shcheduled_timer) {
		has_shcheduled_timer = true;
		scheduleAt(simTime(), timerMessage);
	}
	// debug
}

void Buffer::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {
		handleTimerMessage(msg);
	} else {
		if(dynamic_cast<Flit*>(msg))
			handleFlitMessage(check_and_cast<Flit*>(msg));
		else if(dynamic_cast<Control*>(msg))
			handleControlMessage(check_and_cast<Control*>(msg));
		else
			ASSERT(0);
	}
}

}; // namespace
