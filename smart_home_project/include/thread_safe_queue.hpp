#ifndef THREAD_SAFE_CYCLIC_BUFFER_H
#define THREAD_SAFE_CYCLIC_BUFFER_H

#include <queue> 
#include <cstdio> 
#include "guard.hpp"
#include "mutex.hpp"
#include "condition_variable.hpp"
//#include "condition_variable.inl"
#include "thread.hpp"
#include "uncopyable.hpp"
#include "predicate.hpp"

namespace experis {
    
template <typename T>
class ThreadSafeQueue : private Uncopyable {
public:
	typedef Predicate<ThreadSafeQueue<T> > predicate;
	
public:
	ThreadSafeQueue(size_t a_size = 100);	
	void Enqueue(T a_item);
	void Dequeue(T& a_returnItem);
	size_t GetSize() const;	
	
private:
	friend class Predicate<ThreadSafeQueue<T> >;
		
private:
	bool isFull() const;
	bool isEmptey() const;

private:   
	std::queue<T> m_buffer;
	mutable Mutex m_lock;
	ConditionVariable m_notFull;
	ConditionVariable m_notEmpty;
	size_t m_size;
	size_t m_numOfItems;
	
};

#include "thread_safe_queue.inl"

} //experis

#endif // THREAD_SAFE_CYCLIC_BUFFER_H

