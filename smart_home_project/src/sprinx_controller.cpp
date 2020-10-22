#include "sprinx_controller.hpp"

namespace sh {

SprinxController::SprinxController(const AgentDetails& a_detailes, Subscriber& a_subscriber)
: EventHandler()
, ControllerAgent(a_detailes, a_subscriber) 
{
}

SprinxController::~SprinxController() {
}

void SprinxController::HandleEvent(EventPtr a_eventType) {
    std::cout << "receve smoke signal turn on the sprinlers" << std::endl;
}

} //sh

