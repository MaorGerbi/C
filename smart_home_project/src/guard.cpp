#include "guard.hpp"

namespace experis {

Guard::Guard(Mutex& a_mutex)
: m_mutex(a_mutex) {
	m_mutex.Lock();
}

Guard::~Guard() {
	m_mutex.Unlock();
}

}// experis
