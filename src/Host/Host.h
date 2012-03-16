//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __HOST_H__
#define __HOST_H__

#include <omnetpp.h>
#include "common.h"

#include "Flit_m.h"
#include "Credit_m.h"

#include "TrafficPatterns.h"


namespace n_radix_switch {

#define HOST_CREDITS 16

class Host : public cSimpleModule
{
private:
	int dim;
	int self_address;

	int flits_sent;

	int packet_size;
	int flit_size;
	int credit_size;

	cMessage* timerMessage;
	Flit *pFlitMessage;
	TrafficPatterns *traffic_pattern;

	int tx_credits;
	simtime_t send_ia_duration;
	simtime_t packet_duration;
	simtime_t flit_duration;
	simtime_t tx_timestamp;
	int packet_to_send;
	bool generate_packets;
	int total_flits_received;
	int total_packets_received;
	int total_flits_sent;
	int total_packets_sent;


	simtime_t head_timestamp;
	simtime_t total_latency;
	simtime_t kthroughput;

#ifdef DEBUG
	int rx_sequnce_number;
	int rx_flit_kind;
#endif
	bool bFirstPacket;

#ifdef DEBUG
    int currnet_destination;
#endif

protected:
	virtual void initialize();
	virtual void finish();
	virtual void handleMessage(cMessage *msg);

	void sendMessage(cMessage *msg, simtime_t delay, const char *gatename);

	Flit * createHeadFlit();
	Flit * createPayloadFlit();
	Flit * createTailFlit();
	Flit * createFlit(int *flit_kind);

	void handleTimerMessage(cMessage *msg);

	void handleCreditMessage(Credit* Credit);
	void handleFlitMessage(Flit *pFlit);

	void handleStatMessage(cMessage *msg);
	void UpdateDisplay(Flit *pFlit);

    cStdDev Latency;
    cStdDev Throughput ;

public:
	Host();
	virtual ~Host();
;

};

}; // namespace

#endif
