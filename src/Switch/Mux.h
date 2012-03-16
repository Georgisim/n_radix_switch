/*
 * Buffer.h
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef MUX_H_
#define MUX_H_

#include <omnetpp.h>
#include "common.h"

#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {

class Mux : public cSimpleModule
{
private:
	int selected_channel;

public:
	Mux();
	virtual ~Mux();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);

	void handleFlitMessage(Flit *pFlit);
	void handleControlMessage(Control *pControl);
	void handleTimerMessage(cMessage *msg);
};



}; // namespace switch4x

#endif /* MUX_H_ */
