#ifndef Neighbour_H_
#define Neighbour_H_

#include "TrafficPatterns.h"

namespace n_radix_switch {

class Neighbour : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
	int	_n, _k, _xr;
public:
	Neighbour(int n, int k, int self_address);
	~Neighbour();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
