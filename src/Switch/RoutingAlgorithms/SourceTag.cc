#include "SourceTag.h"

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */


SourceTagRouting::SourceTagRouting(int n, int k, int slef_address)
{
	_n = n;
	_k = k;
	dim = pow(k, n);

	slef_address_array = new int[n];
	_slef_address = slef_address;

	//EV << "slef_address_array=";

	memset(slef_address_array, 0, sizeof(int) * n);
	for(int j = 0; j < n; j++) {
		slef_address_array[j] = slef_address % _k;
		slef_address /= _k;

	//	EV << slef_address_array[j] << ", ";
	}
	//EV << endl;

}

SourceTagRouting::~SourceTagRouting()
{
	delete slef_address_array;
}



int SourceTagRouting::GetOutputNumber(Flit *pFlit)
{
	int dest = pFlit->getDestination();

//	EV << "SourceTagRouting, dest=" << dest << endl;
//	EV  << _slef_address << " -> " << dest << endl;

	return dest;

	ASSERT(0);
	return -1;
}

} // namespace
