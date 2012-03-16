/*
 * Buffer.cc
 *
 *  Created on: 2011-26-1
 *      Author: George
 */

#include "Mux.h"
#include "Flit_m.h"


namespace n_radix_switch {

Define_Module(Mux);



Mux::Mux()
{

}

Mux::~Mux()
{

}

void Mux::initialize()
{

}

void Mux::handleControlMessage(Control *pControl)
{

}



void Mux::handleFlitMessage(Flit *pFlit)
{
	switch (pFlit->getKind()) {
		case FLIT_HEAD:
			selected_channel = pFlit->getOutput_port();
			break;
		case FLIT_PAYLOAD:
			break;
		case FLIT_TAIL:
			break;
	}

	send(pFlit, "out", selected_channel);
}


void Mux::handleMessage(cMessage *msg)
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
