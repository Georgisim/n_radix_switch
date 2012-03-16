#ifndef TRAFFICPATTERNS_H_
#define TRAFFICPATTERNS_H_

#include "Flit_m.h"

namespace n_radix_switch {


class TrafficPatterns {

public:
	TrafficPatterns();
	~TrafficPatterns();

	virtual int GetDestination(int source) = 0;
};


class TrafficPatternsFactory {

public:
	static TrafficPatterns *NewTrafficPattern(const char* traffic_funct, int n, int k, int self_address);
};

}; // n_radix_switch


#endif
