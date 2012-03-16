/*
 * Regiter.cc
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#include "common.h"
#include "outPort.h"

namespace n_radix_switch {

Define_Module(outPort);

outPort::outPort()
{

}

outPort::~outPort()
{

}

void outPort::initialize()
{
	nports = par("nports").longValue();

}

void outPort::finish()
{

}

void outPort::UpdateDisplay(Flit *pFlit)
{
// colors
	cDisplayString dispStr = getDisplayString();
	switch (pFlit->getKind()) {
		case FLIT_HEAD:
			dispStr.setTagArg("i", 1, "green");
			break;
		case FLIT_PAYLOAD:
			dispStr.setTagArg("i", 1, "blue");
			break;
		case FLIT_TAIL:
			dispStr.setTagArg("i", 1, "black");
			break;
	}
	setDisplayString(dispStr);
}



void outPort::handleControlMessage(Control *pControl)
{

}


void outPort::sendMessage(cMessage *msg, const char *gatename)
{
	cChannel *txChannel = gate(gatename)->getTransmissionChannel();
	simtime_t txFinishTime = txChannel->getTransmissionFinishTime();

	if (txFinishTime <= simTime())
		sendDelayed(msg, 0, gatename);
	else
		sendDelayed(msg, txFinishTime - simTime(), gatename);
}

void outPort::handleFlitMessage(Flit *pFlit)
{
	sendMessage(pFlit, "out");
	UpdateDisplay(pFlit);
}

void outPort::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {

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
