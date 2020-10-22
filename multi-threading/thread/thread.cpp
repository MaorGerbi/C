#include "thread.hpp"

namespace experis {

Thread::Thread(Routine& a_routine)
: m_isJoinable(false)
, m_isDetach(false) {
	int statusCode = pthread_create(&m_thread, NULL, StartRoutine, &a_routine);
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
}
//
void Thread::Detach() {
	if (m_isDetach || m_isJoinable) {
		return;
	}
	m_isDetach = true;
	int statusCode =pthread_detach(m_thread);
		if (0 != statusCode) {
			switch (statusCode) {
				case ESRCH:
					assert(!"Impossible erro code");
				case EINVAL: 
					assert(!"Impossible erro code");
			}
		}
}

		
void Thread::Join() {
	if (m_isDetach || m_isJoinable) {
		return;
	}
	m_isJoinable = true;
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
}
 	


Thread::~Thread() {
	if (false == m_isJoinable && false == m_isDetach) { 
		assert(!"You forgot to set a thread join/detach");
	}
}

void* Thread::StartRoutine(void* a_routine) {
	Routine* routine = reinterpret_cast<Routine*> (a_routine);
	routine->RunFunction();
	return NULL;
}

} //experis
