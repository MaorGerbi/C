#ifndef SMART_HOME_CONTROLLER_AGENT_HPP
#define SMART_HOME_CONTROLLER_AGENT_HPP

#include <tr1/memory>
#include <string>
#include "agent_details.hpp"
#include "subscriber.hpp"
#include "event_key.hpp"
#include "event_handler.hpp"
#include "controller_agent.hpp"
#include "subscribe_details.hpp"

namespace sh {

class ControllerAgent : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr <EventHandler> EventHandlerPtr;
    typedef std::tr1::shared_ptr <SubscribeDetails> SubscribeDetailsPtr;

public:
    ControllerAgent(const AgentDetails& m_detailes, Subscriber& a_subscriber);
    virtual ~ControllerAgent();
 
    void Subscribe(std::tr1::shared_ptr <SubscribeDetails> a_subInfo, EventHandlerPtr a_hendler);   

private:
    AgentDetails m_details;
    Subscriber& m_subscriber;

}; 

} //sh

#endif //SMART_HOME_CONTROLLER_AGENT_HPP
