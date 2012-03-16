#include "BitComplement.h"
#include <math.h>

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

BitComplement::BitComplement(int n, int k, int self_address)
{
	_n_nodes = pow(k, n);
	_self_address = self_address;
}

BitComplement::~BitComplement()
{

}



int BitComplement::GetDestination(int source)
{
	int mask;
	EV << "BitComplement::BitComplement" << endl;

	ASSERT((source >= 0) && (source < _n_nodes));
	mask   = _n_nodes - 1;
	return ~source & mask;
}

} // namespace
