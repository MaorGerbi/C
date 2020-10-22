#ifndef SMART_HOME_CENTRAL_HUB_H
#define SMART_HOME_CENTRAL_HUB_H

#include <tr1/memory>
#include "uncopyable.hpp"
#include "controller_agent.hpp"
#include "event_handler.hpp"
#include "event.hpp"
#include "agent_details.hpp"
#include "extract_handle.hpp"
#include "distributor.hpp"

namespace sh {

class CentralHub : private experis::Uncopyable {
public:
	typedef std::tr1::shared_ptr<Event> EventPtr;
	typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;
	
public:
	CentralHub(const ExtractorHandle& a_extractorHandle);
	// ~CentralHub(); = default
		
private:
	void createAgents();
	void activateAllAgents();
	void run();
	
private:
	const ExtractorHandle& m_extHandles;
	Distributor m_distributor;
	std::vector<EventHandlerPtr> m_controllerAgents;

	
};

} //sh

#endif //SMART_HOME_CENTRAL_HUB_H

