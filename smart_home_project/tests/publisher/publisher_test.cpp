#include "mu_test.h"
#include <string>
#include "publisher.hpp"

BEGIN_TEST(publish)
    static const size_t expectNumOfItems = 3;
    sh::EventPtr e1(new sh::Event("fire", "Data", "location"));  
    sh::EventPtr e2(new sh::Event("open door", "Data", "location")); 
    sh::EventPtr e3(new sh::Event("smoke", "Data", "location")); 
    experis::ThreadSafeQueue<sh::EventPtr> safeQeueu(10);
    sh::Publisher p(safeQeueu); 
   
    p.Publish(e1);
    p.Publish(e2);
    p.Publish(e3);

    ASSERT_EQUAL(safeQeueu.GetSize(), expectNumOfItems);

    sh::EventPtr item1;
    safeQeueu.Dequeue(item1);
    ASSERT_EQUAL(e1, item1);
   
    sh::EventPtr item2;
    safeQeueu.Dequeue(item2);
    ASSERT_EQUAL(e2, item2);

END_TEST

BEGIN_SUITE(publisher)
    TEST(publish)

END_SUITE


