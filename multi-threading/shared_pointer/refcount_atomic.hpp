#ifndef __REFCOUNT_ATOMIC__
#define __REFCOUNT_ATOMIC__

#include <atomic> 
#include "mutex.hpp"

namespace experis {

class RefcountAtomic {
public: 
 	RefcountAtomic();
 	//~RefcountAtomic();
	void operator++();
	bool operator--();

private:
	RefcountAtomic(const RefcountAtomic& a_other); //forbidden
	RefcountAtomic& operator=(const RefcountAtomic& a_other); //forbidden
	std::atomic<size_t> refcount (0);
};

void RefcountAtomic::operator++() {
	++m_refcount;
}

bool RefcountAtomic::operator--() {
	--m_refcount;
		//if(0 == m_refcount) {      // problem to return the curent value because its change
		 							 //problem to retrn  bool and oprate DTOR ref count and thread on mutex (that destroy)   
			//return true;
		//}
	m_mutex.Unlock();
}	

#endif //__REFCOUNT_ATOMIC__
