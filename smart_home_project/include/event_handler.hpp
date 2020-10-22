#ifndef SMART_HOME_EVENT_HANDLER_HPP
#define SMART_HOME_EVENT_HANDLER_HPP

#include "uncopyable.hpp"
#include "agent_details.hpp"
#include "event.hpp"
//#include "smart_home.hpp"

namespace sh {

class EventHandler : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<Event> EventPtr;
    
public:
    //EventHandler() = default;
    virtual ~EventHandler();
    virtual void HandleEvent(EventPtr a_e) = 0;
};

} //sh

#endif //SMART_HOME_EVENT_HANDLER_HPP
