#include <tr1/memory>
#include <iostream>
#include "mu_test.h"
#include "thread.hpp"
#include "mutex.hpp"
#include "guard.hpp"

experis::Mutex lock;
bool passPoint = false;
bool firstEntry = true;
 
void ThrowFunc () {
	experis::Guard g(lock);
	std::cout << "in func" ;
	if (firstEntry) {
		firstEntry = false;
		throw "throw when mutex lock";
	}
	passPoint = true;
}

struct MyRoutine : public experis::Routine {
	virtual void RunFunction() {
		try {
			ThrowFunc();
		}
		catch(...){}
	}
};

BEGIN_TEST(exeption_save)
	std::tr1::shared_ptr<MyRoutine> job(new MyRoutine());
	experis::Thread t1(job);
	experis::Thread t2(job);
	t1.Join();
	t2.Join(); 
	ASSERT_THAT(passPoint);
END_TEST

BEGIN_SUITE(thread_test)
	TEST(exeption_save)
END_SUITE	
	
