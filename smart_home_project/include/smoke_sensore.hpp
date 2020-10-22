#ifndef SMART_HOME_SMOKE_SENSORE_HPP
#define SMART_HOME_SMOKE_SENSORE_HPP

#include "uncopyable.hpp"
#include "publisher.hpp"
#include "agent_details.hpp"
#include "routine.hpp"
#include "thread.hpp"

namespace sh {
class SmokeSensore : private experis::Uncopyable {
public:
    typedef Event::EventPtr EventPtr;

public:
	SmokeSensore(Publisher& a_publisher, const AgentDetails& a_details);
    //~smokeSensore() = default; 

    void virtual Start(); 
	void SendEvent(EventPtr a_event);

private:
	Publisher& m_publisher;
    AgentDetails m_details;
}; 

}// sh

#endif //SMART_HOME_SMOKE_SENSOR_HPP
