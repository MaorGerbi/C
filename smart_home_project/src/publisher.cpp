#include "publisher.hpp"

namespace sh {

Publisher::Publisher(EventQueue& a_eventQueue)
: m_eventQueue(a_eventQueue)
{
}

void Publisher::Publish(EventPtr a_event) {
	m_eventQueue.Enqueue(a_event);
}

} //sh

