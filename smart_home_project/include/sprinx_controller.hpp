#ifndef SMART_HOME_SPRINX_CONTROLLER_HPP
#define SMART_HOME_SPRINX_CONTROLLER_HPP

#include <tr1/memory>
#include "uncopyable.hpp"
#include "agent_details.hpp"
#include "event.hpp"
#include "event_handler.hpp"
#include "controller_agent.hpp"
#include "subscribe_details.hpp"
class Subscriber;

namespace sh {

class SprinxController : public EventHandler, public ControllerAgent {
public:
	typedef std::tr1::shared_ptr<Event> EventPtr;
	typedef std::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;

public:
    SprinxController(const AgentDetails& m_detailes, Subscriber& a_subscriber);
    ~SprinxController();
    
	//virtual void Subscribe(SubscribeDetailsPtr a_details) const;
	virtual void HandleEvent(EventPtr a_e);

private:
	//AgentDetails m_details;
	//Subscriber& m_subscriber;
};

}//sh

#endif //SMART_HOME_SPRINX_CONTROLLER_HPP
