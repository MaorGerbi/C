#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <exception>
#include <assert.h>
#include <errno.h>
#include "uncopyable.hpp"

namespace experis {

namespace mutex {

struct TryToDestroyWhileLock : public std::exception { };
struct TooMany : public std::exception { };

} //mutex

class Mutex : public Uncopyable {

public:
	Mutex();
	~Mutex();
	
	void Unlock();
	void Lock();
	pthread_mutex_t m_lock;
	friend class ConditionVariable;
};
	
} //experis

#endif //MUTEX_H	

