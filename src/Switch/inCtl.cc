/*
 * Buffer.cc
 *
 *  Created on: 2011-26-1
 *      Author: George
 */

#include "inCtl.h"
#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {

Define_Module(inCtl);



inCtl::inCtl()
{

}

inCtl::~inCtl()
{

}

void inCtl::initialize()
{
	credit_size = par("CreditSize").longValue();
}

void inCtl::sendMessage(cMessage *msg, const char *gatename)
{
	cChannel *txChannel = gate(gatename)->getTransmissionChannel();
	simtime_t txFinishTime = txChannel->getTransmissionFinishTime();

	if (txFinishTime <= simTime())
		sendDelayed(msg, 0, gatename);
	else
		sendDelayed(msg, txFinishTime - simTime(), gatename);
}

void inCtl::handleControlMessage(Control *pControl)
{
	switch(pControl->getKind()) {
	case CTL_BUFFER_CREDIT:
		char caption[10];
		sprintf(caption, "%d credits", pControl->getCredits());
		Credit *pCredit = new Credit("credit");
		pCredit->setVcId(0);
		pCredit->setBitLength(credit_size);
		pCredit->setCredits(pControl->getCredits());
		sendMessage(pCredit, "out_credit");
		break;
	}

	delete pControl;
}


void inCtl::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {

	} else {
		if(dynamic_cast<Control*>(msg))
			handleControlMessage(check_and_cast<Control*>(msg));
		else
			ASSERT(0);
	}
}

}; // namespace
