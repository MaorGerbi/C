#ifndef _GUARD_
#define _GUARD_

#include "mutex.hpp"
#include <vector>

namespace experis {
class Guard {

public: 
	Guard(Mutex& a_mutex);
	~Guard();
	void Disable();
	
private:
	Guard(const Guard& a_othe);
	Guard& operator=(const Guard& a_othe);
	
private:
	Mutex& m_mutex;
	bool m_mutexIsValid;
};

/******cpp file*****/

Guard::Guard(Mutex& a_mutex)
: m_mutexIsValid(true)
, m_mutex(a_mutex) {
}

void Guard::Disable() {
	m_mutexIsValid = false;
}

Guard::~Guard() {
	if (m_mutexIsValid) {
		m_mutex.Unlock();
	}
}
	
} //experis

#endif // _GUARD_
