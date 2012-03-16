#include "HotSpot.h"

namespace n_radix_switch {


HotSpot::HotSpot(int n, int k, int self_address)
{
	_n_nodes = pow(k, n);
	_self_address = self_address;
}

HotSpot::~HotSpot()
{

}



int HotSpot::GetDestination(int source)
{

	EV << "Hello from" << "HotSpot::GetDestination" << endl;
	return 5;
}

} // namespace
