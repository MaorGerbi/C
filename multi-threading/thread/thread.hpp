#ifndef THREAD_H
#define THREAD_H

#include <exception> 
#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include "routine.hpp"

namespace experis {
namespace thread {

struct OperationSystemError : public std::exception {
};
} //thread

class Thread {
public:
	Thread(Routine& a_routine);
	~Thread();
	void Join();
	void Detach();
	
private:
	Thread(const Thread& a_thread); //forbidden
	Thread& operator=(const Thread& a_thread); //forbidden
	static void* StartRoutine(void* a_routine);
	
private:
	pthread_t m_thread;
	bool m_isJoinable;
	bool m_isDetach;
};
	
} //experis
#endif //THREAD_H

