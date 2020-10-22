#include "mu_test.h"

#include <typeinfo>
#include <iostream>
#include <memory>
#include <string>
#include "subscribe_details.hpp"
#include "key_protocol.hpp"

BEGIN_TEST(convert_to_key)
    sh::KeyProtocol protocol;
    typedef std::shared_ptr <sh::Key> KeyPtr;
    typedef std::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;

    SubscribeDetailsPtr a(new sh::SubscribeDetails("smoke", "1", "1"));

    KeyPtr keyptr = protocol.ConvertToKey(*a);
    ASSERT_THAT(typeid(*keyptr) == typeid(sh::SSS_key));
    ASSERT_EQUAL(keyptr->Type(), 6);

    SubscribeDetailsPtr b(new sh::SubscribeDetails("smoke","all","1"));
    KeyPtr keyptr1 = protocol.ConvertToKey(*b);
    ASSERT_THAT(typeid(*keyptr1) == typeid(sh::SAS_key));
    ASSERT_EQUAL(keyptr1->Type(), 5);
    
    SubscribeDetailsPtr c(new sh::SubscribeDetails("light","all","all"));
    KeyPtr keyptr2 = protocol.ConvertToKey(*c);
    ASSERT_THAT(typeid(*keyptr2) == typeid(sh::SAA_key));
    ASSERT_EQUAL(keyptr2->Type(), 4);


    SubscribeDetailsPtr d(new sh::SubscribeDetails("all","3","-1"));
    KeyPtr keyptr3 = protocol.ConvertToKey(*d);
    ASSERT_THAT(typeid(*keyptr3) == typeid(sh::ASS_key));
    ASSERT_EQUAL(keyptr3->Type(), 3);


    SubscribeDetailsPtr e(new sh::SubscribeDetails("all","all","-1"));
    KeyPtr keyptr4 = protocol.ConvertToKey(*e);
    ASSERT_THAT(typeid(*keyptr4) == typeid(sh::AAS_key));
    ASSERT_EQUAL(keyptr4->Type(), 2);

    SubscribeDetailsPtr f(new sh::SubscribeDetails("all","all","all"));
    KeyPtr keyptr5 = protocol.ConvertToKey(*f);
    ASSERT_THAT(typeid(*keyptr5) == typeid(sh::AAA_key));
    ASSERT_EQUAL(keyptr5->Type(), 1);

END_TEST

BEGIN_SUITE(key_protocol)
    TEST(convert_to_key)

END_SUITE




//allevent,allfloars,allrooms - key 1 -AAA_key V 
//allevent, allfloars, sps    - key 2 -AAS_key V
//all event, spsfic, spsific  - key 3  ASS_key V

//sp , all, all                -key 4  SAA_key V  
//sps, all ,sps                -key 5  SAS_key 
//sp , sp, sp                  -key 6  SSS_key V