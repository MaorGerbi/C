#ifndef THREAD_H
#define THREAD_H

#include <tr1/memory>
#include <exception> 
#include <pthread.h>
#include <errno.h>
#include <assert.h>
#include "mutex.hpp"
#include "guard.hpp"
#include "routine.hpp"
#include "rendezvous.hpp"
#include "uncopyable.hpp"

namespace experis {

namespace thread {

struct OperationSystemError : public std::exception { };

} //thread

class Thread : private Uncopyable {
public:
	Thread(std::tr1::shared_ptr<Routine> a_routine);
	~Thread();
	
	void Join();
	void Detach();
	
private:
	typedef std::pair<Thread*, std::tr1::shared_ptr<Routine>* > Pair;
	
private:
	static void* StartRoutine(void* a_routine);
	
private:
	bool m_canJoinOrDetach;
	pthread_t m_thread;
	Mutex m_lock;
	sh::Rendezvous m_randPoint;
};
	
} //experis

#endif //THREAD_H

