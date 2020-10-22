#ifndef SMART_HOME_AGENT_HPP
#define SMART_HOME_AGENT_HPP

#include <unistd.h>
#include "event.hpp"
#include "agent.hpp"

namespace sh {

class SensoreAgent :/* public Agent  private experis::Uncopyable*/ {
public:
    SensoreAgent() = default;
    virtual ~SensoreAgent();

	void virtual Start() const = 0;
		
private:
	void sendEvent(Publisher::EventPtr a_event) const = 0;
	//const std::string& Agent::Type() const

private:
	//AgentDetails m_details;
};

} //sh

#endif // SMART_HOME_AGENT_HPP

