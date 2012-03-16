/*
 * Buffer.h
 *
 *  Created on: 2009-11-1
 *      Author: George
 */

#ifndef Queue_H_
#define Queue_H_

#include <omnetpp.h>
#include "common.h"

#include "Flit_m.h"
#include "Control_m.h"

namespace n_radix_switch {


class Buffer : public cSimpleModule
{
private:
	int BufferLengh;
	int *CreditsAvailable;
	int RTtreshold;
	int nvcs;
	cQueue *queue;

	Channel_t currnt_channel;
	cMessage* timerMessage;
	simtime_t switch_clock;
	bool has_shcheduled_timer;
public:
	Buffer();
	virtual ~Buffer();

protected:
	virtual void initialize();
	virtual void finish();
	virtual void handleMessage(cMessage *msg);

	void handleTimerMessage(cMessage *msg);
	void handleFlitMessage(Flit *pFlit);
	void handleControlMessage(Control *pControl);
	void UpdateDisplay(int count);
};

}; // namespace switch4x

#endif /* Buffer_H_ */
