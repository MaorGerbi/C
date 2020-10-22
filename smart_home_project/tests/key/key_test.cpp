#include "mu_test.h"

#include <typeinfo>
#include <iostream>
#include <memory>
#include <string>
#include "aaa_key.hpp"
#include "aas_key.hpp"
#include "ass_key.hpp"
#include "saa_key.hpp"
#include "sas_key.hpp"
#include "sss_key.hpp"
#include "key_protocol.hpp"

sh::KeyProtocol protocol;

BEGIN_TEST(sss_key)
    sh::SSS_key b(6, "smoke", "1", "2");
    sh::SSS_key c(6, "smoke", "7", "1");
    sh::SSS_key d(6, "fire", "1", "2");
    typedef std::shared_ptr<sh::Key> KeyPtr;
    KeyPtr keyptr = protocol.ConvertToKey("smoke", "1", "1");

    ASSERT_THAT(typeid(*keyptr) == typeid(sh::SSS_key));
    std::shared_ptr<sh::SSS_key> a =  std::dynamic_pointer_cast<sh::SSS_key>(keyptr);

    if ( (*a) < b) {
        ASSERT_THAT(true);
    }
    else {
       ASSERT_FAIL("a < b !");
    }
    if ( d < c) {
         ASSERT_THAT(true);
    }
    else {
            ASSERT_FAIL("d < c !");
    }
END_TEST

BEGIN_TEST(sas_key)
    sh::SAS_key a(5, "open_door", "2");
    sh::SAS_key b(5, "fire", "1");
    sh::SAS_key c(5, "fire" , "2");

    if ( c < a) {
        ASSERT_THAT(true);
    }
    else {
       ASSERT_FAIL("c < a !");
    }
    if ( b < c) {
         ASSERT_THAT(true);
    }
    else {
            ASSERT_FAIL("d < c !");
    }

END_TEST
BEGIN_TEST(saa_key)
    sh::SAA_key a(4, "open_door");
    sh::SAA_key b(4, "fire");
    sh::SAA_key c(4, "fire_e");

    if ( b < a) {
        ASSERT_THAT(true);
    }
    else {
       ASSERT_FAIL("c < a !");
    }
    if ( b < c) {
         ASSERT_THAT(true);
    }
    else {
            ASSERT_FAIL("d < c !");
    }
END_TEST

BEGIN_TEST(ass_key)
    sh::SAS_key a(3, "5", "2");
    sh::SAS_key b(3, "5", "1");
    sh::SAS_key c(3, "1" , "2");

    if ( c < b) {
        ASSERT_THAT(true);
    }
    else {
       ASSERT_FAIL("c < b !");
    }
    if ( b < a) {
         ASSERT_THAT(true);
    }
    else {
            ASSERT_FAIL("b < a !");
    }
END_TEST

BEGIN_TEST(aas_key)
    sh::AAS_key a(2, "0");
    sh::AAS_key b(2, "1");
    sh::AAS_key c(2, "2");

    if ( b < c) {
        ASSERT_THAT(true);
    }
    else {
        ASSERT_FAIL("b < c !");
    }
    if ( a < b) {
            ASSERT_THAT(true);
    }
    else {
            ASSERT_FAIL("b < a !");
    }
END_TEST

BEGIN_TEST(aaa_key)
    sh::AAA_key c(2);
    ASSERT_THAT(true);
END_TEST

BEGIN_SUITE(keys)
    TEST(sss_key)
    TEST(sas_key)
    TEST(saa_key)
    TEST(ass_key)
    TEST(aas_key)
    TEST(aaa_key)
END_SUITE



//allevent,allfloars,allrooms - key 1 -AAA_key V 
//allevent, allfloars, sps    - key 2 -AAS_key V
//all event, spsfic, spsific  - key 3  ASS_key V -V

//sp , all, all                -key 4  SAA_key V -V
//sps, all ,sps                -key 5  SAS_key V -V
//sp , sp, sp                  -key 6 SSS_key  V- V


    
