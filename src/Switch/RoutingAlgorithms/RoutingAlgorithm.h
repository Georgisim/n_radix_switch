#ifndef ROUTING_H_
#define ROUTING_H_

#include "Flit_m.h"

namespace n_radix_switch {


class Routing {

public:
	Routing();
	~Routing();

	virtual int GetOutputNumber(Flit *pFlit) = 0;
};


class RoutingFactory {

public:
	static Routing *NewRouting(const char* routing_funct, int n, int k, int slef_address);
};

}; // n_radix_switch


#endif
