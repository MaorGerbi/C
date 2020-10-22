#ifndef SMART_HOME_CONDITION_VARIABLE_H
#define SMART_HOME_CONDITION_VARIABLE_H

#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h>
#include <iostream>
#include "mutex.hpp"

namespace experis {

namespace exceptions {

    struct IllegalMutex : public std::exception { };
    struct LackOfSystemResources : public std::exception { };
    struct SignalIllegalCondition : public std::exception { };  
              
} // exceptions

class ConditionVariable : private Uncopyable { 
public:
    ConditionVariable();
    ~ConditionVariable();
    
    void Signal();
    
    template <typename T>
    void Wait(Mutex& a_lock,const T& a_predicate);
    
private:
    pthread_cond_t m_condition;
};

} //experis

#endif// SMART_HOME_CONDITION_VARIABLE_H

