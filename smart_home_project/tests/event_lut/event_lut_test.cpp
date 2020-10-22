#include "mu_test.h"

#include "event_lut.hpp"
#include "sprinx_controller.hpp"
#include "subscribe_details.hpp"
#include "sprinx_controller.hpp"


BEGIN_TEST(add_and_search)
    typedef std::tr1::shared_ptr<sh::SubscribeDetails> SubscribeDetailsPtr;
    sh::EventLut lut;
    sh::Subscriber sub(lut);
    sh::AgentDetails d("id-432-test", "sprinx","floor1, room3", "test");
    std::tr1::shared_ptr<sh::SprinxController> agent(new sh::SprinxController(d,sub));

    sh::AgentDetails d1("id-420-test", "sprinx","floor1, room3", "test2");
    std::tr1::shared_ptr<sh::SprinxController> agent1(new sh::SprinxController(d1,sub));

    SubscribeDetailsPtr subDetails1(new sh::SubscribeDetails("smoke","1","1"));
    SubscribeDetailsPtr subDetails2(new sh::SubscribeDetails("fire","all","21"));
    SubscribeDetailsPtr subDetails3(new sh::SubscribeDetails("smoke","21","1"));

    SubscribeDetailsPtr subDetails4(new sh::SubscribeDetails("all","all","all"));
    SubscribeDetailsPtr subDetails5(new sh::SubscribeDetails("all","all","1"));
    SubscribeDetailsPtr subDetails6(new sh::SubscribeDetails("all","4","1"));

    lut.Add(subDetails1, agent);
    lut.Add(subDetails2, agent);
    lut.Add(subDetails3, agent);

    lut.Add(subDetails4, agent1);
    lut.Add(subDetails5, agent1);
    lut.Add(subDetails6, agent1);
    ASSERT_EQUAL(lut.Size(), 6);
    //for search
    SubscribeDetailsPtr subDetails7(new sh::SubscribeDetails("fire","4","1"));  

    sh::EventLut::Value resCon = lut.Search(subDetails1); //expect agemt 1 ,agent2 , agent 2
    sh::EventLut::Value resCon1 = lut.Search(subDetails7); ////expect agent2 ,agent2

    ASSERT_EQUAL(agent1, resCon[0]);
    ASSERT_EQUAL(agent, resCon[1]);
    ASSERT_EQUAL(agent1, resCon1[0]);
END_TEST

BEGIN_SUITE(event_lut)
    TEST(add_and_search)
END_SUITE
