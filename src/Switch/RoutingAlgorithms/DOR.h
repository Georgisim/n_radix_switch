#ifndef DOR_H_
#define DOR_H_

#include "Flit_m.h"
#include "RoutingAlgorithm.h"

namespace n_radix_switch {

class DORRouting : public Routing {
private:
	int dim;
	int _n;
	int _k;
	int _slef_address;
	int *slef_address_array;
public:
	DORRouting(int n, int k, int slef_address);
	~DORRouting();
	virtual int GetOutputNumber(Flit *pFlit);
};

}; // n_radix_switch

#endif
