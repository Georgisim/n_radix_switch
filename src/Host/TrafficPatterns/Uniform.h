#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "Flit_m.h"
#include "TrafficPatterns.h"

namespace n_radix_switch {

class Uniform : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
public:
	Uniform(int n, int k, int self_address);
	~Uniform();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
