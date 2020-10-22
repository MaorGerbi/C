#include "controller_agent.hpp"

namespace sh {

ControllerAgent::ControllerAgent(const AgentDetails& a_details, Subscriber& a_subscriber)
:	m_details(a_details)
,	m_subscriber(a_subscriber)
{
}

ControllerAgent::~ControllerAgent() {
}

void ControllerAgent::Subscribe(SubscribeDetailsPtr a_subInfo, EventHandlerPtr a_hendler) {
	m_subscriber.Subscribe(a_hendler, a_subInfo);
}

} //sh
