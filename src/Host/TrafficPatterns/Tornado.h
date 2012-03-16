#ifndef Tornado_H_
#define Tornado_H_

#include "TrafficPatterns.h"

namespace n_radix_switch {

class Tornado : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
	int	_n, _k,	_xr;
public:
	Tornado(int n, int k, int self_address);
	~Tornado();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
