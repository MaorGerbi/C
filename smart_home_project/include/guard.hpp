#ifndef GUARD_H
#define GUARD_H

#include "uncopyable.hpp"
#include "mutex.hpp"

namespace experis {

class Guard :private Uncopyable{

public: 
	Guard(Mutex& a_mutex);
	~Guard();

private:
	Mutex& m_mutex;
};
	
} //experis

#endif // GUARD_H

