#include "BitReversal.h"
#include <math.h>

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

BitReversal::BitReversal(int n, int k, int self_address)
{
	_n_nodes = pow(k, n);
	_self_address = self_address;
}

BitReversal::~BitReversal()
{

}



int BitReversal::GetDestination(int source)
{
	int destination = 0;
	EV << "Hello from" << "BitReversal::BitReversal" << endl;

	ASSERT((source >= 0) && (source < _n_nodes));

	for(int i = _n_nodes; i > 1; i >>= 1) {
		destination = (destination << 1) | (source % 2);
		source >>= 1;
	}
	EV << "BitReversal::BitReversal(" << source << ")=" << destination << endl;

	return destination;
}

} // namespace
