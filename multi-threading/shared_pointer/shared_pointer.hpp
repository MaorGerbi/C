#ifndef __SHARED_PTR__
#define __SHARED_PTR__

namespace experis {

template <typename T>
class SharedPtr {

public:
	SharedPtr(T* a_ptr);
	~SharedPtr();
	
	SharedPtr(const SharedPtr& a_other);
	SharedPtr& operator=(const SharedPtr& a_other);
	T* operator->() const;
	T& operator*() const;
	
private:
	void decreamntCounterPtr();

private:
	T* m_ptr;
	unsigned int* m_ptrCounter;	
};

template <typename T>
SharedPtr <T>::SharedPtr(T* a_ptr)
: m_ptr(a_ptr)
, m_ptrCounter(new unsigned int) {
	*m_ptrCounter = 1;
}

template <typename T>
SharedPtr <T>::~SharedPtr() {
	decreamntCounterPtr();
}

template <typename T>
void SharedPtr <T>::decreamntCounterPtr() {
	--(*m_ptrCounter);
	if (0 == *m_ptrCounter) {
		if(NULL != m_ptr) {
			delete  m_ptr;
		}
		delete  m_ptrCounter;
	}
}

template <typename T>
T* SharedPtr <T>::operator->() const {
	return m_ptr;
}
	
template <typename T>
SharedPtr <T>::SharedPtr(const SharedPtr& a_other) {
	++(*a_other.m_ptrCounter);
	m_ptr = a_other.m_ptr;
	m_ptrCounter = a_other.m_ptrCounter;
}	

template <typename T>
T& SharedPtr <T>::operator*() const {
	return *m_ptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& a_other) {
	if (this != &a_other) { 
		++(*(a_other.m_ptrCounter));
		decreamntCounterPtr();
		m_ptr = a_other.m_ptr;
		m_ptrCounter = a_other.m_ptrCounter;
	}
	return *this;
}	

} //experis		 
#endif // __SHARED_PTR__
