#include "mu_test.h"

#include <string>
#include "smoke_sensore.hpp"
#include "publisher.hpp"
#include <iostream>

BEGIN_TEST(ctor_and_run)
    typedef sh::Event::EventPtr EventPtr;
    static const size_t expectItems = 3;
    sh::AgentDetails d("id:1234","smoke_sene","floor1, room2", "test");
    sh::Event expectEvent("smoke_detactor", "room 12", "test");
    experis::ThreadSafeQueue<EventPtr> queue;
    sh::Publisher p(queue);
    sh::SmokeSensore sense(p, d);
    
    sense.Start();
    sleep(4);
    ASSERT_EQUAL(queue.GetSize(),  expectItems);

    EventPtr eventInQueue;
    for(size_t i= 0 ; i < expectItems; ++i) {
         queue.Dequeue(eventInQueue);
         ASSERT_EQUAL(expectEvent.Type(), eventInQueue->Type());
         ASSERT_EQUAL(expectEvent.Location(), eventInQueue->Location());
         ASSERT_EQUAL(expectEvent.Data(), eventInQueue->Data());
    }
   
END_TEST

BEGIN_SUITE(smoke_sensore)
    TEST(ctor_and_run)

END_SUITE
