/*
 * Buffer.cc
 *
 *  Created on: 2011-26-1
 *      Author: George
 */

#include "inRegister.h"
#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {

Define_Module(inRegister);



inRegister::inRegister()
{

}

inRegister::~inRegister()
{

}

void inRegister::initialize()
{
	const char *routing_funct =	par("RoutingAlgorithm").stringValue();

	routing = RoutingFactory::NewRouting(routing_funct, par("n").longValue(), par("k").longValue(), par("self_address").longValue());
}


void inRegister::handleFlitMessage(Flit *pFlit)
{
//	int vc = pFlit->getVcId();
	int output;

	switch(pFlit->getKind()) {
	case FLIT_HEAD:
		output = routing->GetOutputNumber(pFlit);
		pFlit->setOutput_port(output);
		pFlit->setVcId(0);
		break;
	case FLIT_PAYLOAD:
#ifdef DEBUG
		output = routing->GetOutputNumber(pFlit);
		pFlit->setOutput_port(output);
		pFlit->setVcId(0);
#endif
		break;
	case FLIT_TAIL:
#ifdef DEBUG
		output = routing->GetOutputNumber(pFlit);
		pFlit->setOutput_port(output);
		pFlit->setVcId(0);
#endif
		break;
	}
	pFlit->setHops_count(pFlit->getHops_count() + 1);

	send(pFlit, "out");
}


void inRegister::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {

	} else {
		if(dynamic_cast<Flit*>(msg))
			handleFlitMessage(dynamic_cast<Flit*>(msg));
		else
			ASSERT(0);
	}
}

}; // namespace
