#include "mu_test.h"

#include <stdlib.h> 
#include <iomanip>
#include <unistd.h>
#include <tr1/memory>
#include "thread.hpp"
#include "rendezvous.hpp"

sh::Rendezvous randPoint;
int g_counter;
int g_detachFlag = false;
bool g_joinFlag = false;
static const int SelectCtor = 1;
static const int selectJoin = 2;
static const int selectDetach = 3;

void JoinTest() { 
	sleep(2);
	g_joinFlag = true;
}

void CtorTest() { 
	for(int i = 0; i < 100000000; ++i) {
		++g_counter;
	}
}

void DetachTest() { 
	sleep(2);
	g_detachFlag = true;
	randPoint.Notifay();
}

class MultiCheckRoutine : public experis::Routine {
public:
	MultiCheckRoutine(int a_testFunc)
	: m_testFunc(a_testFunc)
	{
	}

private:
	virtual void RunFunction() {
		switch (m_testFunc) {
			case SelectCtor:
				CtorTest();
				break;
			case selectJoin:
				JoinTest();
				break;
			case selectDetach:
				DetachTest();
				break;
			default:
				break;
		}
	}
	
private:
	int m_testFunc;
};

BEGIN_TEST(CTOR)
	std::tr1::shared_ptr<MultiCheckRoutine> job(new MultiCheckRoutine(SelectCtor));
	experis::Thread t1(job);
	experis::Thread t2(job);
	t1.Join();
	t2.Join(); 
	ASSERT_EQUAL(g_counter , 100000000*2);	
END_TEST

BEGIN_TEST(join)
	std::tr1::shared_ptr<MultiCheckRoutine> job(new MultiCheckRoutine(selectJoin));
	experis::Thread t1(job);
	t1.Join();
	ASSERT_THAT(g_joinFlag);
END_TEST

BEGIN_TEST(detach)
	{
		std::tr1::shared_ptr<MultiCheckRoutine> job(new MultiCheckRoutine(selectDetach));
		experis::Thread t1(job);
		t1.Detach();
		//main thread go sleep while the new thread access to the routine do function 
		sleep(1); 
	}   //DETOR t1 & job
	randPoint.Wait();
	ASSERT_THAT(g_detachFlag);
		
END_TEST

BEGIN_SUITE(thread_test)
    TEST(CTOR)
    TEST(join)
    TEST(detach)
END_SUITE
