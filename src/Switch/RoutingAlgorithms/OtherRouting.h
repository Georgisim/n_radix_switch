#ifndef OTHER_H_
#define OTHER_H_

#include "Flit_m.h"
#include "RoutingAlgorithm.h"

namespace n_radix_switch {

class OtherRouting : public Routing {
private:
	int dim;
	int _n;
	int _k;
	int _slef_address;

public:
	OtherRouting(int n, int k, int slef_address);
	~OtherRouting();
	int GetOutputNumber(Flit *pFlit);
};

}; // n_radix_switch

#endif
