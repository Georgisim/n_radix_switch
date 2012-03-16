#include "OtherTraffic.h"

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

OtherTrafficPattern::OtherTrafficPattern(int n, int k, int self_address)
{
	_n_nodes = pow(k, n);
	_self_address = self_address;
}

OtherTrafficPattern::~OtherTrafficPattern()
{

}



int OtherTrafficPattern::GetDestination(int source)
{

	EV << "Hello from" << "OtherTrafficPattern::OtherTrafficPattern" << endl;
	return 0;
}

} // namespace
