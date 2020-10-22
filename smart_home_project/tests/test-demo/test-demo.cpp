#include "mu_test.h"

#include <climits>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

double pi(size_t n) {
    double sum = 0.0;
    int sign = 1;
    for (size_t i = 0; i < n; ++i) {           
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}


BEGIN_TEST(pi_raw_short_test)
    double p = pi(1000);
    TRACER << fixed << setprecision(10);
    TRACER << "\t\ttaylor: " << p << " delta: " << M_PI - p << '\n';
    ASSERT_THAT(std::abs(p-M_PI) < 1e-2);
END_TEST

BEGIN_TEST(pi_raw_long_test)
    double p = pi(100000);
    TRACER << fixed << setprecision(10);
    TRACER << "\t\ttaylor: " << p << " delta: " << M_PI - p << '\n';
    ASSERT_THAT(std::abs(p-M_PI) < 1e-4);
END_TEST

BEGIN_TEST(pi_raw_very_long_test)
    double p = pi(500000);
    TRACER << fixed << setprecision(10);
    TRACER << "\t\ttaylor: " << p << " delta: " << M_PI - p << '\n';
    ASSERT_THAT(std::abs(p-M_PI) < 1e-4);
END_TEST

BEGIN_TEST(pi_raw_ultra_long_test)
    double p = pi(2000000);
    TRACER << fixed << setprecision(10);
    TRACER << "\t\ttaylor: " << p << " delta: " << M_PI - p << '\n';
    ASSERT_THAT(std::abs(p-M_PI) < 1e-4);
END_TEST

BEGIN_TEST(panic)
    int* p = 0;
    *p = 42;

    ASSERT_FAIL("what? can't dereference null");

END_TEST

BEGIN_TEST(div_ints)
    int a = 17;
    int b = 8;
    ASSERT_EQUAL(a/b , 2);

    std::string s("hello");
    ASSERT_EQUAL(s, s);
    ASSERT_EQUAL(s, "Hello");
    
END_TEST

BEGIN_TEST(add_ints_big)
    int a = INT_MAX / 2;
    ++a;
    int b = INT_MAX / 2;
    ++b;


    long r = a + b;
    TRACER << "r is " << r <<'\n';    
    
    ASSERT_THAT(r > 0);
END_TEST

BEGIN_TEST(large_alloc)        
    int* p = 0;
    int *q = 0;
    try {
        p = new int[92233720];
        ASSERT_PASS();
        ASSERT_THAT(p);
        q = new int[9223372036854775];
    }catch(...){
        delete q;
        delete p;        
        ASSERT_FAIL("failed to alloc large chunk!");
    }

END_TEST

BEGIN_SUITE(mu test frameqwork demo!)
    TEST(panic)
    TEST(div_ints)
    IGNORE_TEST(add_ints_big)
    
    TEST(pi_raw_short_test)
    TEST(pi_raw_long_test)
    TEST(pi_raw_very_long_test)
    TEST(pi_raw_ultra_long_test)

    TEST(large_alloc)
END_SUITE

