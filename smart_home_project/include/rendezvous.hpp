#ifndef SMART_HOME_RENDEZVOUS_H
#define SMART_HOME_RENDEZVOUS_H

#include "guard.hpp"
#include "mutex.hpp"
#include "uncopyable.hpp"
#include "is_arrived.hpp"
#include "condition_variable.hpp"
#include "condition_variable.inl"

namespace sh {

class Rendezvous : private experis::Uncopyable {
public:
	Rendezvous();
	void Wait();	
	void Notifay();

private:
	experis::Mutex m_mutex;
	experis::ConditionVariable m_cond;
	bool m_isArrived;
};

}// sh

#endif //SMART_HOME_RENDEZVOUS_H

