#include "event.hpp"
#include <iostream>
//#include "smart_home.hpp"

int main() { 
	sh::Event e("EVENT ", "IS ", "PASS !");
	
	std::cout <<e.Type()<<e.Data()<<e.Location() << std::endl;
    
    std::cout << "this event created on: " << e.TimeStamp() << std::endl;
	return 0;
}
