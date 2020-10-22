#include "mutex.hpp"

namespace experis {
Mutex::Mutex() {
    int statusCode = pthread_mutex_init(&m_lock, NULL);
    if (0 != statusCode) {
    	switch (statusCode) {
			case EINVAL:
				assert(!"Impossible erro code");
			case EBUSY: 
				assert(!"Impossible erro code");
			default:
				assert(!"Undocumented error code");
	    }   
    }
}

Mutex::~Mutex() {
	int statusCode = pthread_mutex_destroy(&m_lock);
	/* TODO
	if (0 != statusCode) {
		switch (statusCode) {
			case EBUSY:
				throw mutex::TryToDestroyWhileLock();
			case EINVAL:
				assert(!"Impossible erro code");
			default:
				assert(!"Undocumented error code"); 
		}
	}*/
}
				
void Mutex::Lock() {
	 int statusCode = pthread_mutex_lock(&m_lock);
	 if(0 != statusCode) {
	 	switch (statusCode) {
			case EINVAL:
				assert(!"Impossible erro code");
			case EAGAIN:
				throw mutex::TooMany();
			case EDEADLK:
				assert(!"Impossible erro code");
			default:
				assert(!"Undocumented error code");
		}
	}
}

void Mutex::Unlock() {
	int  statusCode = pthread_mutex_unlock(&m_lock); 
	if(0 != statusCode) {
		switch (statusCode) {
			case EINVAL:
				assert(!"Impossible erro code");
			case EAGAIN:
				throw mutex::TooMany();
			case EPERM:
				assert(!"Impossible erro code");
			default:
				assert(!"Undocumented error code");
		}
	}
}
} //experis
