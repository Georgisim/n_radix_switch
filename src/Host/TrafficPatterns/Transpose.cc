#include "Transpose.h"
#include <math.h>

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

Transpose::Transpose(int n, int k, int self_address)
{
	int i = _n_nodes = pow(k, n);
	_self_address = self_address;
	_shift = 0;
	while(i >>= 1) {
		++_shift;
	}
	EV << "_shift=" << _shift << endl;
	ASSERT(_shift % 2 == 0); /* Transpose traffic pattern requires the number of nodes to  e an even power of two. */
   _shift >>= 1;
}

Transpose::~Transpose()
{

}



int Transpose::GetDestination(int source)
{
	int mask_lo, mask_hi;
	EV << "Transpose::Transpose(" << source << ")" << endl;

	ASSERT((source >= 0) && (source < _n_nodes));

	mask_lo = (1 << _shift) - 1;
	mask_hi = mask_lo << _shift;

	int destination = (((source >> _shift) & mask_lo) | ((source << _shift) & mask_hi));
	EV << "Transpose::Transpose(" << source << ")="  << destination << endl;

	return (((source >> _shift) & mask_lo) | ((source << _shift) & mask_hi));

}

} // namespace
