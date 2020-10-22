#include <stdlib.h> 
#include <climits>
#include<iostream>
#include<iomanip>
#include<cmath>
#include "mu_test.h"
#include "thread.hpp"


int g_numOfThread;
int g_counter;

void Race() { 
		++g_counter;
}

struct MyRoutine : public experis::Routine {
	virtual void RunFunction() {
		Race();
	}
};



BEGIN_TEST(CTOR)
	MyRoutine job;
	experis::Thread t1(job);
	experis::Thread t2(job);
	t1.Join();
	t2.Join(); 
	std::cout << g_counter;
	ASSERT_THAT(2 == g_counter);	
END_TEST

BEGIN_TEST(join)
	MyRoutine job;
	experis::Thread t1(job);
	t1.Join();
	++g_numOfThread;
	ASSERT_THAT(1 == g_numOfThread);
END_TEST
	

BEGIN_TEST(detach)
	g_numOfThread = 0;
	MyRoutine job;
	experis::Thread t1(job);
	t1.Detach();
	t1.Join();
	++g_numOfThread;
	ASSERT_THAT(1 == g_numOfThread);	
END_TEST

BEGIN_SUITE(thread_test)
    TEST(CTOR)
    TEST(join)
    TEST(detach)
END_SUITE
