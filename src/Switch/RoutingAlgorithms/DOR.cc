#include "DOR.h"

namespace n_radix_switch {


/*
 *  Calculates routing decision and stores output port where the Flit will leave the switch.
 *  Current one implements  Dimension Ordered Routing(DOR)
 *
 *   for n-ary, k-cube, address is expressed as Sum Ai . k^i, i = 0..n-1
 *
 */


DORRouting::DORRouting(int n, int k, int slef_address)
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

DORRouting::~DORRouting()
{
	delete slef_address_array;
}



int DORRouting::GetOutputNumber(Flit *pFlit)
{
	int dest = pFlit->getDestination();

//	EV << "DORRouting" << endl;
//	EV  << _slef_address << " -> " << dest << endl;

	if(_slef_address == dest) {
		// EV << "host=" << 2 * _n << endl;
		return 2 * _n;
	}

	for(int j = 0; j < _n; j++) {
		int res;

		res = dest % _k;
		dest /= _k;

		// EV << "" << j << ":  " <<  slef_address_array[j] << " -> " << res << endl;
		if(res < slef_address_array[j]) {
			// EV << "low output=" << j << endl;
			return j;
		} else if(res > slef_address_array[j]) {
			// EV << "high output=" << j + _n << endl;
			return j + _n;
		}
	}

	ASSERT(0);
	return -1;
}

} // namespace
