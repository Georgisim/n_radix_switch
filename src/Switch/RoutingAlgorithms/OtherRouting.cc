#include "OtherRouting.h"

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */

OtherRouting::OtherRouting(int n, int k, int slef_address)
{
	_n = n;
	_k = k;
	dim = pow(k, n);
	_slef_address = slef_address;
}

OtherRouting::~OtherRouting()
{

}



int OtherRouting::GetOutputNumber(Flit *pFlit)
{
	EV << "Hello from" << "OtherRouting" << endl;

	return 0;
}

} // namespace
