/*
 * outPort.h
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef outPort_H_
#define outPort_H_

#include <omnetpp.h>
#include "common.h"


#include "Flit_m.h"
#include "Control_m.h"


namespace n_radix_switch {


class outPort : public cSimpleModule
{
private:
	int nports;

	cMessage* timerMessage;
public:
	outPort();
	virtual ~outPort();

protected:
	virtual void initialize();
	virtual void finish();
	virtual void handleMessage(cMessage *msg);

	void handleTimerMessage(cMessage *msg);
	void handleFlitMessage(Flit *pFlit);
	void handleControlMessage(Control *pControl);
	void sendMessage(cMessage *msg, const char *gatename);

	void UpdateDisplay(Flit *pFlit);
};

}; // namespace switch4x

#endif /* outPort_H_ */
