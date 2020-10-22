#ifndef __REFCOUNT_MUTEX__
#define __REFCOUNT_MUTEX__

#include "mutex.hpp"

namespace experis {

class RefcountMutex {
public: 
 	RefcountMutex();
 	//~RefcountMutex();
	void operator++();
	bool operator--();

private:
	RefcountMutex(const RefcountMutex& a_other); //forbidden
	RefcountMutex& operator=(const RefcountMutex& a_other); //forbidden
	size_t m_refcount;
	Mutex m_mutex;
};

void RefcountMutex::operator++() {
	m_mutex.Lock();
	++m_refcount;
	m_mutex.Unlock();
}

bool RefcountMutex::operator--() {
	m_mutex.Lock();
	--m_refcount;
		//if(0 == m_refcount) {      // problem to return the curent value because its change
		 							 //problem to retrn  bool and oprate DTOR ref count and thread on mutex (that destroy)   
			//return true;
		//}
	m_mutex.Unlock();
}	
