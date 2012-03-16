#ifndef HotSpot_H_
#define HotSpot_H_

#include "Flit_m.h"
#include "TrafficPatterns.h"

namespace n_radix_switch {

class HotSpot : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
public:
	HotSpot(int n, int k, int self_address);
	~HotSpot();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
