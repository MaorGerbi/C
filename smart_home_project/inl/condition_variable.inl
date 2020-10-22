
namespace experis {

template <typename T>
void ConditionVariable::Wait(experis::Mutex& a_lock,const T& a_predicate) {
	while (a_predicate()) {
		int statusCode = pthread_cond_wait(&m_condition, &(a_lock.m_lock));
		switch (statusCode) {
		case ETIMEDOUT:
			assert(!"Impossible");
		case EINVAL:
			throw exceptions::IllegalMutex();
		case EPERM:
			assert(!"Impossible");
		}
	}                          
} 

} //experis


