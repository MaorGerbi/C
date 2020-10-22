#include "semaphore.hpp"

namespace experis {

Semaphore::Semaphore(SemType a_semType, size_t a_semValue) {
	int statusCode = sem_init(&m_semaphore, a_semType, a_semValue);
		if (0 != statusCode) {
			switch (statusCode) {
				case EINVAL:
					throw semaphore::OperationSystemError();
					break;
				case ENOSYS: 
					throw semaphore::OperationSystemError();	
					break;		
				default:
					assert(!"Undocumented error code");
			}   
		}
}

Semaphore::~Semaphore() {
	int statusCode = sem_destroy(&m_semaphore);
	if (0 != statusCode) {
		switch (statusCode) {
			case EINVAL:
				assert(!"Impossible erro code");
			default: 
				assert(!"Undocumented error code");
		}
	}
}

void Semaphore::Wait() {
	int statusCode = sem_wait(&m_semaphore);
		if (0 != statusCode) {
		switch (statusCode) {
			case EINTR:
				throw semaphore::IgnorSignal();
				break;
			case EINVAL:
				assert(!"Impossible erro code");
				break;
			case EAGAIN: 
				throw semaphore::HasZeroValue();
				break;
			case ETIMEDOUT: 
				assert(!"Impossible erro code");	
				break;		
			default:
				assert(!"Undocumented error code");
		}   
	}
}	

void Semaphore::Notify() {
	int statusCode = sem_post(&m_semaphore);
		if (0 != statusCode) {
			switch (statusCode) {
				case EOVERFLOW:
					throw semaphore::OverFlew();
					break;
				case EINVAL:
					assert(!"Impossible erro code");	
					break;		
				default:
					assert(!"Undocumented error code");
			}
		}   	
}
	
} //experis
