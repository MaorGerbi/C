#include "distributor.hpp"

namespace sh {

 void Distributor::Distribute(std::vector <EventHandlerPtr> a_handelContainer, Event::EventPtr a_event) {
	std::vector<EventHandlerPtr>::iterator it = a_handelContainer.begin();
    while(it != a_handelContainer.end()) {
        (*it)->HandleEvent(a_event);
        ++it;
    }
 }

} //sh
