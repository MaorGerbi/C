#ifndef _MUTEX_
#define _MUTEX_

#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <exception>
#include <assert.h>
#include <errno.h>

namespace experis {
namespace mutex {

struct TryToDestroyWhileLock : public std::exception {
};
struct TooMany : public std::exception {
};

} //mutex
class Mutex {

public:
	Mutex();
	~Mutex();
	
	void Unlock();
	void Lock();
	
private:
	Mutex(const Mutex& a_mutex); //forbidden
	Mutex& operator=(const Mutex& a_mutex); //forbidden
	pthread_mutex_t m_lock;
};
	
} //experis
#endif //_MUTEX_	
