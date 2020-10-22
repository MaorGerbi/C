#ifndef SMART_HOME_EXTRACT_HANDLE_HPP
#define SMART_HOME_EXTRACT_HANDLE_HPP

#include <vector>
#include <tr1/memory>
#include "uncopyable.hpp"
#include "geter.hpp"
#include "dequeuer.hpp"
#include "event_handler.hpp"

namespace sh {

class ExtractorHandle : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;
    typedef std::tr1::shared_ptr<SubscribeDetails> SubscribeDetailsPtr;

public:
    ExtractorHandle(const Geter& a_geter, Dequeuer& a_deqer);
    // ~ExtractorHandle() = default;
    Event::EventPtr GetCurrentEvent() const;
    std::vector<EventHandlerPtr> BringNewHandlers(Event::EventPtr a_Key) const;
    
private:
    const Geter& m_geter;
    Dequeuer&  m_deqer;
    std::vector <EventHandlerPtr> m_controllerAgents;

};



}//sh


#endif //SMART_HOME_EXTRACT_HANDLE_HPP