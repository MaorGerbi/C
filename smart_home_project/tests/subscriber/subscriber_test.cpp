#include "subscriber.hpp"
#include "sprinx_controller.hpp"


int main() {
   
    sh::EventLut lut;
    sh::Subscriber sub(lut);
    const sh::AgentDetails d("id-432", "sprinx","floor1, room3", "test");
    sh::EventKey key("fire", "1", "2");

    sh::EventHandler * sp = new sh::SprinxController(d, sub);
    std::tr1::shared_ptr <sh::EventHandler> sprinx(sp);

    sub.Subscribe(sprinx, key);
    
    return 0;
}
