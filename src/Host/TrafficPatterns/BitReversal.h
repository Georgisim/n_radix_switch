#ifndef BitReversal_H_
#define BitReversal_H_

#include "TrafficPatterns.h"

namespace n_radix_switch {

class BitReversal : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
public:
	BitReversal(int n, int k, int self_address);
	~BitReversal();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
