/*
 * Buffer.h
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef inRegister_H_
#define inRegister_H_

#include <omnetpp.h>
#include "common.h"
#include "RoutingAlgorithm.h"

#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {


class inRegister : public cSimpleModule
{
private:
	Routing *routing;

public:
	inRegister();
	virtual ~inRegister();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);

	void handleFlitMessage(Flit *pFlit);
};



}; // namespace switch4x

#endif /* Buffer_H_ */
