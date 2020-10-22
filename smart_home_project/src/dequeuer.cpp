#include "dequeuer.hpp"

namespace sh {

Dequeuer::Dequeuer(EventQueue& a_eventQueue)
: m_eventQueue(a_eventQueue)
{
}

void Dequeuer::Dequeue(EventPtr& a_event) {
	m_eventQueue.Dequeue(a_event);
}

} //sh

