#include <vector>
#include <tr1/memory>
#include "thread_safe_queue.hpp"
#include "mu_test.h"
#include "iostream"

namespace experis {
bool testResult = true;
ThreadSafeQueue<size_t> safeQeueue(10);

void Enqueque(size_t a_upRange, size_t a_downRange) {
	for (size_t i = a_downRange; i < a_upRange; ++i) {
		safeQeueue.Enqueue(i);
	}
}

void Dequeue(std::vector<size_t>& a_container, size_t a_range) {
	size_t item = 0;
	for (size_t i = 0; i < a_range; ++i) {
		safeQeueue.Dequeue(item);
		a_container.push_back(item);
	}
}

void CheckItemsOrder(std::vector<size_t>& a_container, size_t a_range) {
	size_t expectItem1 = 0, expectItem2 = a_range / 2;
	for (size_t i = 0; i < a_range; ++i) {
		if (a_container[i] == expectItem1) {
			++expectItem1;
		}
		else if (a_container[i] == expectItem2) {
			++expectItem2;
		}
		else {
			testResult = false;
			break;
		}
	}
}

class EnqueueRoutine : public Routine {
public:
	EnqueueRoutine(size_t a_upRange, size_t a_downRange) 
	: m_upRange(a_upRange)
	, m_downRange(a_downRange)
	{
	}	
	
private:
	virtual void RunFunction() { 
		Enqueque(m_upRange, m_downRange);
	}
		
private:
	size_t m_upRange;
	size_t m_downRange;
};

class DequeueRoutine : public Routine {
public:
	DequeueRoutine(std::vector<size_t>& a_container, size_t a_range) 
	: m_range(a_range)
	, m_container(a_container)
	{
	}	
	
private:
	virtual void RunFunction() { 
		Dequeue(m_container, m_range);
		CheckItemsOrder(m_container, m_range);
	}
		
private:
	size_t m_range;
	std::vector<size_t>& m_container;
};

} //experis

BEGIN_TEST(one_consumer_one_producer)
	size_t up = 2, down = 0;
	std::vector<size_t> container;
 	std::tr1::shared_ptr<experis::EnqueueRoutine> inqueueJob(new experis::EnqueueRoutine(up, down));
	std::tr1::shared_ptr<experis::DequeueRoutine> deququJob(new experis::DequeueRoutine(container, up));
	experis::Thread worker2(deququJob);
	sleep(1);
	experis::Thread worker1(inqueueJob);
	worker1.Join();
	worker2.Join();
	ASSERT_THAT(experis::testResult);
END_TEST

BEGIN_TEST(one_consumer_two_producer)	
	size_t up = 1000, down = 0, mid = up/2;
	std::vector<size_t> container;
	std::tr1::shared_ptr<experis::DequeueRoutine> deququJob(new experis::DequeueRoutine(container, up));
	std::tr1::shared_ptr<experis::EnqueueRoutine> inqueueJob(new experis::EnqueueRoutine(mid, down));
	std::tr1::shared_ptr<experis::EnqueueRoutine> inqueueJob2(new experis::EnqueueRoutine(up, mid));	
	experis::Thread worker3(deququJob);
	
	sleep(1);
	experis::Thread worker1(inqueueJob);
	
	sleep(1);
	experis::Thread worker2(inqueueJob2);
	
	worker1.Join();
	worker2.Join();
	worker3.Join();
	ASSERT_THAT(experis::testResult);
END_TEST

BEGIN_SUITE(thread_safe_queue)
	TEST(one_consumer_one_producer)
	TEST(one_consumer_two_producer)
END_SUITE
