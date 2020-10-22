#include "sprinx_controller.hpp"
#include "event_key.hpp"

void TestHandleEvent() {
    typedef std::tr1::shared_ptr<sh::Event> EventPtr;
    typedef std::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;
    sh::EventLut lut;
    sh::Subscriber sub(lut);
    sh::AgentDetails d("id-432", "sprinx","floor1, room3", "test");
    EventPtr e(new sh::Event("smoke_signal", "test","flor1,room3"));
    SubscribeDetailsPtr subD(new sh::SubscribeDetails("test","1","3"));
    std::tr1::shared_ptr<sh::SprinxController> agent(new sh::SprinxController(d,sub));

    agent->Subscribe(subD, agent);

    lut.Search(subD);
    agent->HandleEvent(e);
    
}

int main () {
    TestHandleEvent();
    return 0;
}
