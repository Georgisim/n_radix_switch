#ifndef BitComplement_H_
#define BitComplement_H_

#include "TrafficPatterns.h"

namespace n_radix_switch {

class BitComplement : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
public:
	BitComplement(int n, int k, int self_address);
	~BitComplement();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
