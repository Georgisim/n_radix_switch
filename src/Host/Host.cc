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
// You should have handle a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "Host.h"
#include "TrafficPatterns.h"
#include <math.h>

namespace n_radix_switch {

Define_Module(Host);

Host::Host()
{

}

Host::~Host()
{

}

void Host::initialize()
{
    double channel_rate;

    dim = pow(par("n").longValue(), par("k").longValue());
    self_address = par("self_address").longValue();

    traffic_pattern = TrafficPatternsFactory::NewTrafficPattern(par("TrafficPattern").stringValue(), par("n").longValue(), par("k").longValue(), self_address);

    packet_to_send = par("PacketsToSend").longValue();
    packet_size = par("PacketSize").longValue();
    flit_size = par("FlitSize").longValue();
	credit_size = par("CreditSize").longValue();

    timerMessage = new cMessage("timer");
    pFlitMessage = NULL;

    generate_packets = true;

    total_packets_sent = total_flits_sent = flits_sent = 0;
    total_packets_received = total_flits_received = 0;
    tx_credits = 0;

    channel_rate =  gate("out")->getTransmissionChannel()->getNominalDatarate();\
    flit_duration = flit_size / channel_rate;
	packet_duration = flit_size * packet_size / channel_rate;
	send_ia_duration = (100*packet_duration/par("PacketRate").doubleValue() - packet_duration);
	EV << "packet_duration  =" << packet_duration * 1000 << endl;
	EV << "send_ia_duration =" << send_ia_duration * 1000 << endl;
	EV << "packet_rate=" << par("PacketRate").doubleValue() << endl;

	total_latency = kthroughput = 0;
	bFirstPacket = true;
	Credit *pCredit = new Credit("credit");
	pCredit->setVcId(0);
	pCredit->setBitLength(credit_size);
	pCredit->setCredits(HOST_CREDITS);
	send(pCredit, "out_credit");

#ifdef DEBUG
	rx_flit_kind = FLIT_TAIL;
#endif

	Latency.setName("Latengy");
	Throughput.setName("Throughput");
}

void Host::finish()
{
	cancelAndDelete(timerMessage);
	EV << "host[" << self_address <<  "] total_packets_sent:     " << total_packets_sent << endl;
	EV << "host[" << self_address <<  "] total_packets_received: " << total_packets_received << endl;
	EV << "host[" << self_address <<  "] total_flits_sent:     " << total_flits_sent << endl;
	EV << "host[" << self_address <<  "] total_flits_received: " << total_flits_received << endl;
	EV << "host[" << self_address <<  "] total_latency:          " << total_latency << endl;

	Latency.record();

	Throughput.collect(total_flits_received /simTime());
	Throughput.record();
}

void Host::UpdateDisplay(Flit *pFlit)
{
	// debug & colors
	cDisplayString dispStr = getDisplayString();
	switch(pFlit->getKind()) {
		case FLIT_HEAD:
			dispStr.setTagArg("i", 1, "green");
			break;
		case FLIT_PAYLOAD:
			dispStr.setTagArg("i", 1, "blue");
			break;
		case FLIT_TAIL:
			dispStr.setTagArg("i", 1, "white");
			break;

	}
	setDisplayString(dispStr);
}


void Host::handleStatMessage(cMessage *msg)
{
	cMessage *stat_msg;

	ASSERT(msg);
	EV << "handleStatMessage = " << msg->getKind() << endl;
	delete msg;

	stat_msg = new cMessage("stats");
	stat_msg->setKind(STAT_NODE_READY);
	send(new cMessage("stats_status"), "stat_ctl$o");
}

Flit * Host::createHeadFlit()
{
	int destination;

	destination = traffic_pattern->GetDestination(self_address);
#ifdef DEBUG
    currnet_destination = destination;
#endif

	// EV << "destination = " << destination << endl;

	Flit* pFlit = new Flit("Head", FLIT_HEAD);

	pFlit->setDestination(destination);
#ifdef DEBUG
	pFlit->setSource(self_address);
#endif
	// ASSERT(self_address != destination);

	pFlit->setHops_count(0);
	pFlit->setBitLength(flit_size);
	pFlit->setVcId(0); // TODO

	return pFlit;
}

Flit * Host::createPayloadFlit()
{
	Flit* pFlit = new Flit("Payload", FLIT_PAYLOAD);
#ifdef DEBUG
    pFlit->setDestination(currnet_destination);
    pFlit->setSource(self_address);
#else
    pFlit->setDestination(0);
#endif

	pFlit->setBitLength(flit_size);
	pFlit->setVcId(0); // TODO

	return pFlit;
}

Flit * Host::createTailFlit()
{
	Flit* pFlit = new Flit("Tail", FLIT_TAIL);
#ifdef DEBUG
    pFlit->setDestination(currnet_destination);
    pFlit->setSource(self_address);
#else
    pFlit->setDestination(0);
#endif

	pFlit->setBitLength(flit_size);
	pFlit->setVcId(0); // TODO

	return pFlit;
}

Flit * Host::createFlit(int *flit_kind)
{
	Flit *pFlit;

	if(flits_sent == 0) {
		pFlit = createHeadFlit();
		*flit_kind = FLIT_HEAD;
	} else if(flits_sent == packet_size-1) {
		pFlit = createTailFlit();
		*flit_kind = FLIT_TAIL;
	} else {
		*flit_kind = FLIT_PAYLOAD;
		pFlit = createPayloadFlit();
	}

	total_flits_sent++;
	flits_sent  = total_flits_sent % packet_size;
	pFlit->setHops_count(0);
#ifdef DEBUG
	pFlit->setSequnce_number(total_packets_sent);
#endif

	return pFlit;
}


void Host::handleTimerMessage(cMessage *msg)
{

}


void Host::handleCreditMessage(Credit* pCredit)
{
	int flit_kind;

	if(bFirstPacket == true) {
		tx_timestamp = simTime();
		bFirstPacket = false;
	}

	if(!generate_packets) {
		EV << "total_packets_sent: " << total_packets_sent  << endl;
		delete pCredit;
		return;
	}

	// EV << "Got Credit" << endl;
	tx_credits += pCredit->getCredits();
	delete pCredit;

	while(tx_credits > 0) {
		Flit *pFlit = createFlit(&flit_kind);

		// sendMessage(pFlit, next_period, "out");
		sendMessage(pFlit, tx_timestamp, "out");
		tx_credits--;

		switch(flit_kind) {
		case FLIT_HEAD:
			// pFlit->setTimestamp(tx_timestamp);
			tx_timestamp += flit_duration;
			break;
		case FLIT_TAIL:
			total_packets_sent++;
			if(total_packets_sent >= packet_to_send) {
				generate_packets = false;
				return;
			}

			tx_timestamp += exponential(send_ia_duration + flit_duration);
			break;

		case FLIT_PAYLOAD:
			tx_timestamp += flit_duration;
			break;
		}
	};
}

void Host::sendMessage(cMessage *msg, simtime_t tx_time, const char *gatename)
{
    cChannel *txChannel = gate(gatename)->getTransmissionChannel();
    simtime_t current_finish_time = txChannel->getTransmissionFinishTime();

    msg->setTimestamp(tx_time);

    if (current_finish_time <= tx_time) {
        simtime_t setdelay = tx_time - simTime();
        sendDelayed(msg, (setdelay > 0)?setdelay:0, gatename);
    }
    else {
        simtime_t setdelay = current_finish_time - simTime();
        sendDelayed(msg, (setdelay > 0)?setdelay:0, gatename);
    }
}

void Host::handleFlitMessage(Flit *pFlit)
{
	simtime_t packet_latency;

	switch(pFlit->getKind()) {
	case FLIT_HEAD:
		ASSERT(pFlit->getDestination() == self_address);
		ASSERT(rx_flit_kind == FLIT_TAIL);
		rx_sequnce_number = pFlit->getSequnce_number();
		head_timestamp = pFlit->getTimestamp();
		break;

	case FLIT_PAYLOAD:
		ASSERT(pFlit->getDestination() == self_address);
		ASSERT(rx_flit_kind == FLIT_HEAD || rx_flit_kind == FLIT_PAYLOAD);
		ASSERT(rx_sequnce_number == pFlit->getSequnce_number());
		break;
	case FLIT_TAIL:
		ASSERT(pFlit->getDestination() == self_address);
		ASSERT(rx_flit_kind == FLIT_PAYLOAD);
		ASSERT(rx_sequnce_number == pFlit->getSequnce_number());

		packet_latency = (simTime() - head_timestamp) / pFlit->getHops_count(); // mean per hop

		total_latency += packet_latency;
		Latency.collect(packet_latency);
		total_packets_received ++;

		break;
	}

	rx_flit_kind = pFlit->getKind();

	total_flits_received++;

	delete pFlit;

	Credit *pCredit = new Credit("credit");
	pCredit->setVcId(0);
	pCredit->setBitLength(credit_size);
	pCredit->setCredits(1);
	send(pCredit, "out_credit");
}

void Host::handleMessage(cMessage *msg)
{
	if (msg->isSelfMessage()) {
		handleTimerMessage(msg);
	} else {
		if(dynamic_cast<Flit*>(msg))
			handleFlitMessage(check_and_cast<Flit*>(msg));
		else if(dynamic_cast<Credit*>(msg))
			handleCreditMessage(check_and_cast<Credit*>(msg));
		else
			ASSERT(0);
	}

}


}; // namespace
