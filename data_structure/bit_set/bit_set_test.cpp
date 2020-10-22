#include <iostream>
#include "bit_set.hpp"


void TestClearAll() {
	experis::BitSet<10> bitSet;
    for (int i = 0; i < 10; i += 2) {
        bitSet.Set(i, true);
    }
    bitSet.Print();
    bitSet <<= 5;
    bitSet.Print();
/*
	bitSet.Print();
	bitSet1.Print();
	bitSet.TurnAllOn();
	bitSet1.TurnAllOn();
	bitSet.Print();
	bitSet1.Print();
	bitSet.ClearAll();
	bitSet1.ClearAll();
	bitSet.Print();
	bitSet1.Print();
	bitSet.Set(4, true);
	bitSet.Set(0, true);
	bitSet.Set(9, true);
	bitSet.Set(2, true);
	bitSet[2];
	bitSet.Print();
	std::cout << bitSet.CountAll();
	bitSet.Print();*/

}	



int main () {
	//experis::BitSet<10> bitSet;
	TestClearAll();
	
	return 0;
}

