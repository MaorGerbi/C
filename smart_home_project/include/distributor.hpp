#ifndef SMART_HOME_DISTRIBUTOR_HPP
#define SMART_HOME_DISTRIBUTOR_HPP

#include <vector>
#include "tr1/memory"
#include "uncopyable.hpp"
#include "event_handler.hpp"

namespace sh {

class Distributor : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;

public: 
    //Distributor() = default;
    //~Distributor()= default ;

    void Distribute(std::vector <EventHandlerPtr> a_handelContainer, Event::EventPtr a_event);
};

}//sh

#endif //SMART_HOME_Distributor_HPP