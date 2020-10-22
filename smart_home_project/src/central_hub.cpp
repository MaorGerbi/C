#include "central_hub.hpp"

namespace sh {

CentralHub::CentralHub(const ExtractorHandle& a_extractorHandle)
: m_extHandles(a_extractorHandle)
, m_distributor()
, m_controllerAgents()
{
	createAgents();
	activateAllAgents();
	run();
}

void CentralHub::createAgents() {
	//create all agents sensore and controllers using so file and config info
}

void CentralHub::activateAllAgents() {
	//on the agent controller activate them on by one
}

void CentralHub::run() { //multi thread
	while (true) {
		Event::EventPtr e = m_extHandles.GetCurrentEvent();//Controllers to inform
		std::vector<ExtractorHandle::EventHandlerPtr> agentsToInform = m_extHandles.BringNewHandlers(e);
		m_distributor.Distribute(agentsToInform, e);
	}
}
		
} //sh


