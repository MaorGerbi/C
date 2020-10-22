#include <unistd.h>
#include <iostream>
#include "condition_variable.hpp"
#include "condition_variable.inl"
#include "mu_test.h"
#include "mutex.hpp"

int done = 1;
experis::ConditionVariable condition;
experis::Mutex isDoneMutex;

struct Predecate {
	bool operator()() const { return 1 == done; }
};

void* ThreadFunction(void* a_param) {
    isDoneMutex.Lock();
    Predecate predecate;
    std::cout << "Waiting on con var" << std::endl;
    condition.Wait(isDoneMutex, predecate);
    done = 1 ;
    return NULL; 
}

void* got(void* a_) {
	done = 0; 
	std::cout << "Signaling cond var" << std::endl;
    condition.Signal();  
    return NULL;
}
 
BEGIN_TEST(waitAndSignal)
	experis::ConditionVariable condition;
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, ThreadFunction, NULL);
    sleep(3); 
    pthread_create(&thread2, NULL, got, NULL);
    pthread_join(thread2, NULL);
    ASSERT_THAT(done);
END_TEST

BEGIN_SUITE(condition_variable)
    TEST(waitAndSignal)
END_SUITE
