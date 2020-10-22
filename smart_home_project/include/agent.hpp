#ifndef SMART_HOME_AGENT_HPP
#define SMART_HOME_AGENT_HPP

#include "agent_details.hpp"
#include "uncopyable.hpp"

namespace sh {

class Agent : private experis::Uncopyable {
public:
    Agent(AgentDetails a_details);
    virtual ~Agent();
    const std::string& Type() const;

private:
    AgentDetails m_details; 
};

}//sh

#endif //SMART_HOME_AGENT_HPP

