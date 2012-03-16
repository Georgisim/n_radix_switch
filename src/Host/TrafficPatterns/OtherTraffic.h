#ifndef OtherTrafficPatterns_H_
#define OtherTrafficPatterns_H_

#include "Flit_m.h"
#include "TrafficPatterns.h"

namespace n_radix_switch {

class OtherTrafficPattern : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
public:
	OtherTrafficPattern(int n, int k, int self_address);
	~OtherTrafficPattern();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
