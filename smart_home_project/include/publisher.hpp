#ifndef SMART_HOME_PUBLISHER
#define SMART_HOME_PUBLISHER

#include <tr1/memory>
#include "thread_safe_queue.hpp"
#include "uncopyable.hpp"
#include "event.hpp"

namespace sh {

class Publisher : private experis::Uncopyable {	
public:
	typedef Event::EventPtr EventPtr;
	typedef experis::ThreadSafeQueue <EventPtr> EventQueue;

public:
	Publisher(EventQueue& a_eventQueue);
	//~publisher(); = default
	
	void Publish(EventPtr a_event);
	
private:
	EventQueue& m_eventQueue;
};

} //sh

#endif //SMART_HOME_PUBLISHER
	
