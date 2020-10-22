#include "condition_variable.hpp"

namespace experis {

ConditionVariable::ConditionVariable() {
    int statusCode = pthread_cond_init(&m_condition , NULL);
    if (0 != statusCode) {
        switch(statusCode) {
        case ENOMEM:
        	throw exceptions::LackOfSystemResources();   
        case EAGAIN:
        	throw exceptions::LackOfSystemResources();                                 
        case EBUSY:
        	assert(!"Impossible");                       
        }       
    }
}
  
void ConditionVariable::Signal() {
    int statusCode = pthread_cond_signal(&m_condition);
    if (EINVAL == statusCode) { 
    	throw exceptions::SignalIllegalCondition();  
    }
}

ConditionVariable::~ConditionVariable() {
    pthread_cond_destroy(&m_condition); 
}

} //experis

