#include "agent_details.hpp"
#include <iostream>

int main () {
    sh::AgentDetails a(" OK ","OK ","OK "," PASS !");
    std::cout<< a.Id() << a.Type() << a.Loction() << a.ConfigData() <<std::endl;
    
    return 0;
}
