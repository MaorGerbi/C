#include <string>
#include "smoke_sensore.hpp"
#include "publisher.hpp"
#include "event_lut.hpp"
#include "subscriber.hpp"
#include "dequeuer.hpp"
#include "extract_handle.hpp"
#include "distributor.hpp"
#include "sprinx_controller.hpp"
#include "central_hub.hpp"
#include "subscribe_details.hpp"
#include <iostream>

int main() {
    typedef sh::Event::EventPtr EventPtr;
    typedef std::tr1::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;

    sh::EventLut lut;
    sh::Subscriber sub(lut);

    //controller side 
    sh::AgentDetails d("id-2", "sprinx", "floor1, room3", "test");
    std::tr1::shared_ptr<sh::SprinxController> sprinxAgent(new sh::SprinxController(d,sub));
    SubscribeDetailsPtr subD(new sh::SubscribeDetails("smoke_detactor","1","1"));
    sprinxAgent->Subscribe(subD, sprinxAgent);

    //sensor side
    sh::AgentDetails d1("id-1", "smoke_sene", "floor1, room3", "test");
    experis::ThreadSafeQueue<EventPtr> queue;
    sh::Publisher p(queue);
    sh::SmokeSensore senseAgent(p, d1);
    
    senseAgent.Start();

    sh::Dequeuer dequeuer(queue);
    sh::Geter geter(lut);
    sh::ExtractorHandle extractHandle(geter, dequeuer);
    sh::Distributor dist;
	
	sh::CentralHub hub(extractHandle);
	

	return 0;
}
