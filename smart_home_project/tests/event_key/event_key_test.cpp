#include "mu_test.h"

#include <iostream>
#include "event_key.hpp"

BEGIN_TEST(operatorLess)
    bool res = false;
    sh::EventKey a("smoke", "1", "1");
    sh::EventKey b("smoke", "1", "2");
    sh::EventKey c("smoke", "7", "1");
    sh::EventKey d("fire", "1", "2");

    if ( a < b) {
        res = true;
    }
    else {
        res = false;
    }
    if ( d < c) {
        res = true;
    }
    else {
            res = false;
    }

    ASSERT_THAT(res);
    END_TEST

BEGIN_SUITE(event_key)
    TEST(operatorLess)
END_SUITE
    
