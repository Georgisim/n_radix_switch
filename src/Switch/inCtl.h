/*
 *
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef inCtl_H_
#define inCtl_H_

#include <omnetpp.h>
#include "common.h"
#include "RoutingAlgorithm.h"

#include "Flit_m.h"
#include "Control_m.h"
#include "Credit_m.h"

namespace n_radix_switch {



class inCtl : public cSimpleModule
{
private:
	int credit_size;
public:
	inCtl();
	virtual ~inCtl();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);

	void handleControlMessage(Control *pControl);
	void sendMessage(cMessage *msg, const char *gatename);
};



}; // namespace switch4x

#endif /*  */
