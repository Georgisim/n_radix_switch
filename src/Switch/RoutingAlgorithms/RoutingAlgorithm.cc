#include "DOR.h"
#include "SourceTag.h"
#include "OtherRouting.h"
#include "RoutingAlgorithm.h"

namespace n_radix_switch {

// Define_Module(RoutingFactory);

Routing::Routing()
{

}

Routing::~Routing()
{

}

Routing *RoutingFactory::NewRouting(const char *routing_funct, int n, int k, int slef_address)
{
	if(!strcmp("DOR", routing_funct) )  {
		return new DORRouting(n, k, slef_address);
	}else if(!strcmp("SourceTag", routing_funct) )  {
		return new SourceTagRouting(n, k, slef_address);
	} else if(!strcmp("OtherRouting", routing_funct) )  {
		return new OtherRouting(n, k, slef_address);
	} else {
		ASSERT(0);
	}

	return NULL;
}


} // namespace
