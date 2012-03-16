#include "Neighbour.h"
#include <math.h>

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

Neighbour::Neighbour(int n, int k, int self_address)
{
	_n = n;
	_k = k;
	_xr = 1;
	_n_nodes = pow(k, n);
	_self_address = self_address;
}

Neighbour::~Neighbour()
{

}



int Neighbour::GetDestination(int source)
{
	EV << "Hello from" << "Neighbour::Neighbour" << endl;
	ASSERT((source >= 0) && (source < _n_nodes));

	int offset = 1;
	int result = 0;

	for(int n = 0; n < _n; ++n) {
		result += offset *
		  (((source / offset) % (_xr * _k) + 1) % (_xr * _k));
		offset *= (_xr * _k);
	}
	return result;
}

} // namespace
