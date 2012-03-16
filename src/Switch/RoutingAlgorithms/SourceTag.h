#ifndef SOURCE_TAG_H_
#define SOURCE_TAG_H_

#include "Flit_m.h"
#include "RoutingAlgorithm.h"

namespace n_radix_switch {

class SourceTagRouting : public Routing {
private:
	int dim;
	int _n;
	int _k;
	int _slef_address;
	int *slef_address_array;
public:
	SourceTagRouting(int n, int k, int slef_address);
	~SourceTagRouting();
	virtual int GetOutputNumber(Flit *pFlit);
};

}; // n_radix_switch

#endif
