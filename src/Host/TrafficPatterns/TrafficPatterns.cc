#include "Uniform.h"
#include "HotSpot.h"
#include "BitReversal.h"
#include "BitComplement.h"
#include "Transpose.h"
#include "Tornado.h"
#include "Neighbour.h"
#include "OtherTraffic.h"
#include "TrafficPatterns.h"

namespace n_radix_switch {

// Define_Module(RoutingFactory);

TrafficPatterns::TrafficPatterns()
{

}

TrafficPatterns::~TrafficPatterns()
{

}

TrafficPatterns *TrafficPatternsFactory::NewTrafficPattern(const char* traffic_funct, int n, int k, int self_address)
{
	if(!strcmp("Uniform", traffic_funct) )  {
		return new Uniform(n, k, self_address);
	} else if(!strcmp("HotSpot", traffic_funct) )  {
		return new HotSpot(n, k, self_address);
	} else if(!strcmp("Transpose", traffic_funct) )  {
		return new Transpose(n, k, self_address);
	} else if(!strcmp("BitReversal", traffic_funct) )  {
		return new BitReversal(n, k, self_address);
	} else if(!strcmp("BitComplement", traffic_funct) )  {
		return new BitComplement(n, k, self_address);
	} else if(!strcmp("Tornado", traffic_funct) )  {
		return new Tornado(n, k, self_address);
	} else if(!strcmp("Neighbour", traffic_funct) )  {
		return new Neighbour(n, k, self_address);
	} else if(!strcmp("OtherTraffic", traffic_funct) )  { // use this template if adding new traffic
		return new OtherTrafficPattern(n, k, self_address);
	}else {
		ASSERT(0);
	}

	return NULL;
}


} // namespace
