#ifndef SMART_HOME_DEQUEUER
#define SMART_HOME_DEQUEUER

#include <tr1/memory>
#include "thread_safe_queue.hpp"
#include "uncopyable.hpp"
#include "event.hpp"

namespace sh {

class Dequeuer : private experis::Uncopyable {	
public:
	typedef Event::EventPtr EventPtr;
	typedef experis::ThreadSafeQueue <EventPtr> EventQueue;

public:
	Dequeuer(EventQueue& a_eventQueue);
	//~Dequeuer(); = default
	
	void Dequeue(EventPtr& a_event);
	
private:
	EventQueue& m_eventQueue;
};

} //sh

#endif //SMART_HOME_DEQUEUER
	
