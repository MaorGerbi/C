	
template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(size_t a_size) 
: m_buffer()
, m_lock()
, m_notFull()
, m_notEmpty()
, m_size(a_size)
, m_numOfItems(0)
{
}

template <typename T>
size_t ThreadSafeQueue<T>::GetSize() const {
	Guard mutexGuard(m_lock);
	return m_buffer.size();
}

template <typename T>
void ThreadSafeQueue<T>::Enqueue(T a_item) {
	try {
		Guard mutexGuard(m_lock);
		predicate is_full(*this, m_size);
		m_notFull.Wait<predicate>(m_lock, is_full);
		m_buffer.push(a_item);
		++ m_numOfItems;
		m_notEmpty.Signal();
	}catch(const std::exception& e) { }
}

template <typename T>
void ThreadSafeQueue<T>::Dequeue(T& a_returnItem) {
	try {
		Guard mutexGuard(m_lock);
		predicate is_empty(*this, 0);
		m_notEmpty.Wait<predicate>(m_lock, is_empty);
		a_returnItem = m_buffer.front();
		m_buffer.pop();  //non return point
		-- m_numOfItems;
		m_notFull.Signal();
	}catch(const std::exception& e) { }
	
}

template <typename T>
bool ThreadSafeQueue<T>::isFull() const { 
	return m_numOfItems == m_size; 
}

template <typename T>
bool ThreadSafeQueue<T>::isEmptey() const { 
	return m_numOfItems == 0; 
}


