/*
 *
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef outCtl_H_
#define outCtl_H_

#include <omnetpp.h>
#include "common.h"
#include "RoutingAlgorithm.h"

#include "Flit_m.h"
#include "Control_m.h"
#include "Credit_m.h"

namespace n_radix_switch {

enum GLOBAL_STATE {
	E_IDLE,
	E_ACTIVE,
	E_WAIT_CREDIT,
};



typedef struct {
	Control *pControl;
} InputVector_t;


typedef struct {
	enum GLOBAL_STATE eGlobalState;
	int CreditCount;
	int LastServicedInput;
	InputVector_t *PendingInput;
	Channel_t current_input;
	Channel_t current_out;
} OutputStateVector_t;


class outCtl : public cSimpleModule
{
private:
	int nports;
	int nvcs;

	cMessage* timerMessage;
	simtime_t switch_clock;
	simtime_t previous_timestamp;
public:
	outCtl();
	virtual ~outCtl();
	OutputStateVector_t **out_state_vector;
protected:
	virtual void initialize();
	virtual void finish();
	virtual void handleMessage(cMessage *msg);

	void handleControlMessage(Control *pControl);
	void handleCreditMessage(Credit *pCredit);
	void sendMessage(cMessage *msg, const char *gatename);
	bool DispatchRequest(Control *pControl, OutputStateVector_t *state);

	void handleTimerMessage(cMessage *msg);
};



}; // namespace switch4x

#endif /*  */
