#ifndef __SEMAPHORE__
#define __SEMAPHORE__

#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <exception> 
#include <errno.h>
#include <assert.h>

namespace experis {
namespace semaphore {

struct OperationSystemError : public std::exception {
};
struct HasZeroValue : public std::exception {
};
struct OverFlew : public std::exception {
};
struct IgnorSignal : public std::exception {
};

} //semaphore

class Semaphore {

public:
	typedef enum SemType { 
		THREAD = 0,
		PROSESS
	} SemType;
	Semaphore(SemType a_semType, size_t a_semValue);
	~Semaphore();
	
	void Wait();
	void Notify();

private:
	sem_t m_semaphore;
};

} //experis
#endif //semaphore

