#include "smoke_sensore.hpp"

namespace sh {

class SenseRoutine : public experis::Routine {
public:
	SenseRoutine(SmokeSensore* a_sensore)
	: m_sensore(a_sensore)
	{
	}
	void RunFunction() {
		size_t count = 2;
		for (size_t i = 0; i < count; ++i) {
			SmokeSensore::EventPtr e(new Event("smoke_detactor", "1", "1"));
			m_sensore->SendEvent(e);
			//sleep(1);
		}
	}

private:
	SmokeSensore* m_sensore;
};

SmokeSensore::SmokeSensore(Publisher& a_publisher, const AgentDetails& a_details)
: m_publisher(a_publisher)
, m_details(a_details)
{
}

void SmokeSensore::SendEvent(EventPtr a_event) {
	m_publisher.Publish(a_event);
}

void SmokeSensore::Start() {
	std::tr1::shared_ptr<SenseRoutine> senseRoutine(new SenseRoutine(this));
	experis::Thread sense(senseRoutine);
	sense.Detach();
	sleep(1);
	
}

}// sh
