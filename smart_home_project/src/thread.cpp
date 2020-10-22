#include "thread.hpp"
#include <iostream>
namespace experis {

Thread::Thread(std::tr1::shared_ptr<Routine> a_routine)
: m_canJoinOrDetach(true)
, m_lock()
, m_randPoint()
{
 	Pair pair (this, &a_routine);
	int statusCode = pthread_create(&m_thread, NULL, StartRoutine, static_cast<void*>(&pair));
    if (0 != statusCode) {
    	switch (statusCode) {
			case EINVAL:
				assert(!"Impossible erro code");
			case EAGAIN: 
				throw thread::OperationSystemError();
			case EPERM: 
				throw thread::OperationSystemError();			
			default:
				assert(!"Undocumented error code");
	    }   
    }
    m_randPoint.Wait();
}

void* Thread::StartRoutine(void* a_pair) {
	Pair  *p = static_cast <Pair *> (a_pair);
	std::tr1::shared_ptr<Routine>* routine = p->second;
	assert(routine);
	(p->first)->m_randPoint.Notifay();
	try {
		(*routine)->RunFunction();
	}catch(const std::exception& e) {
		assert(!"user function throw exception");
	}catch(...) {
		assert(!"user function throw exception");
	} 
	return NULL;
}

void Thread::Detach() {
	Guard guard(m_lock);
	if (m_canJoinOrDetach) {
	   	int statusCode = pthread_detach(m_thread);
		if (0 != statusCode) {
			switch (statusCode) {
				case ESRCH:
					assert(!"Impossible erro code");
				case EINVAL: 
					assert(!"Impossible erro code");
			}
		}
	m_canJoinOrDetach = false;
	}
}
	
void Thread::Join() {
	Guard guard(m_lock);
	if (m_canJoinOrDetach) {
		int statusCode = pthread_join(m_thread, NULL);
		if (0 != statusCode) {
			switch (statusCode) {
				case ESRCH:
					assert(!"Impossible erro code1");
				case EINVAL: 
					assert(!"Impossible erro code2");
				case EDEADLK: 
					throw thread::OperationSystemError();			
				default:
					assert(!"Undocumented error code3");
			 } 
		 }
	   m_canJoinOrDetach = false;
	}
}
 	
Thread::~Thread() {
	if (m_canJoinOrDetach) { 
		assert(!"You forgot to set a thread join/detach");
	}
}

} //experis
