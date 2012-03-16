#ifndef Transpose_H_
#define Transpose_H_

#include "Flit_m.h"
#include "TrafficPatterns.h"

namespace n_radix_switch {

class Transpose : public TrafficPatterns {
private:
	int _n_nodes;
	int _self_address;
	int _shift;
public:
	Transpose(int n, int k, int self_address);
	~Transpose();
	virtual int GetDestination(int source);
};

}; // n_radix_switch

#endif
