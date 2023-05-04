/*
 * Buffer.cc
 *
 *  Created on: 2011-26-1
 *      Author: George
 */

#include "outCtl.h"
#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {

Define_Module(outCtl);



outCtl::outCtl()
{

}

outCtl::~outCtl()
{

}

void outCtl::initialize()
{
	nports = par("nports").longValue();
	nvcs = par("nvcs").longValue();

	out_state_vector = new OutputStateVector_t*[nports];

	for (int port= 0; port < nports; port++) {
		out_state_vector[port] = new OutputStateVector_t[nvcs];
		for(int vc=0; vc < nvcs; vc++) {
			// out_state_vector[port][vc].PendingInput = new InputVector_t[nports];
			out_state_vector[port][vc].LastServicedInput = 0;
			for(int in_port=0; in_port < nports; in_port++) {
				out_state_vector[port][vc].eGlobalState = E_IDLE;
				out_state_vector[port][vc].CreditCount = 0;
				// out_state_vector[port][vc].PendingInput[in_port].pControl = NULL;
			}
		}
	}

}

void outCtl::finish()
{

}

void outCtl::handleTimerMessage(cMessage *msg)
{

}



void outCtl::handleControlMessage(Control *pControl)
{
	int vc = pControl->getVcId();
	int out_port = pControl->getPort();
	int in_port = pControl->getArrivalGate()->getIndex();
	OutputStateVector_t *state = &out_state_vector[out_port][vc];
	Control *pCtlCrant;

	if(state->CreditCount == 0) {
		delete pControl;
		return;
	}

	switch(pControl->getKind()) {
		case CTL_REQ_SW:
#ifdef DEBUG
			ASSERT(state->current_out.port == out_port);
#endif
			ASSERT(state->current_input.port == in_port);
			ASSERT(state->eGlobalState == E_ACTIVE);
			pCtlCrant = new Control;
			pCtlCrant->setKind(CTL_GRANT);
			pCtlCrant->setName("CTL_GRANT");
			pCtlCrant->setPort(state->current_out.port);
			state->CreditCount--;
			send(pCtlCrant, "buffer",  state->current_input.port);
			break;

		case CTL_RELEASE_VC:
#ifdef DEBUG
			ASSERT(state->current_out.port == out_port);
#endif
			ASSERT(state->current_input.port == in_port);
			ASSERT(state->eGlobalState == E_ACTIVE);
			state->eGlobalState = E_IDLE;
			pCtlCrant = new Control;
			pCtlCrant->setKind(CTL_GRANT);
			pCtlCrant->setName("CTL_GRANT");
			pCtlCrant->setPort(state->current_out.port);
			state->CreditCount--;
			send(pCtlCrant, "buffer",  state->current_input.port);
			state->current_input.port = -1;
			break;

		case CTL_REQ_VC:
			if(state->eGlobalState == E_IDLE) {
				state->eGlobalState = E_ACTIVE;
				pCtlCrant = new Control;
				pCtlCrant->setKind(CTL_GRANT);
				pCtlCrant->setName("CTL_GRANT");
				pCtlCrant->setPort(out_port);
				state->current_out.port = out_port;
				state->current_input.port = in_port;
				state->CreditCount--;
				send(pCtlCrant, "buffer",  state->current_input.port);
			}
			break;
	}
	
	delete pControl;
}

void outCtl::handleCreditMessage(Credit *pCredit)
{

	int vc = nvcs * pCredit->getVcId();
	int port = pCredit->getArrivalGate()->getIndex();

	out_state_vector[port][vc].CreditCount+= pCredit->getCredits();

	delete pCredit;
}


void outCtl::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {
		handleTimerMessage(msg);
	} else {
		if(dynamic_cast<Control*>(msg))
			handleControlMessage(check_and_cast<Control*>(msg));
		else if(dynamic_cast<Credit*>(msg))
			handleCreditMessage(check_and_cast<Credit*>(msg));
		else
			ASSERT(0);
	}
}

}; // namespace
