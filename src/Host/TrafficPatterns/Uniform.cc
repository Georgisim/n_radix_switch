#include "Uniform.h"
#include <math.h>

namespace n_radix_switch {


Uniform::Uniform(int n, int k, int self_address)
{
	_n_nodes = pow(k, n);
	_self_address = self_address;
	EV << "Uniform::GetDestination n=" << n << ", k=" << k << endl;
}

Uniform::~Uniform()
{

}



int Uniform::GetDestination(int source)
{
	int dest;


	do {
		dest = intuniform(0, _n_nodes-1);
	} while (dest == _self_address); // do not include ourself

	// EV << "Uniform::GetDestination " << _self_address << " -> " << dest << endl;

	return dest;
}

} // namespace
