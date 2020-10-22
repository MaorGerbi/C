#ifndef SMART_HOME_SUBSCRIBE_DETAILS_HPP
#define SMART_HOME_SUBSCRIBE_DETAILS_HPP

#include <string>

namespace sh { 

class SubscribeDetails {
public:
    SubscribeDetails(std::string a_event, std::string a_floor, std::string a_room);
    //~SubcribeDEtails() = default;
    
    //SubcribeDEtails(const SubcribeDEtails& a_other) = default;
    //SubcribeDEtails& operator=(const SubcribeDEtails& a_other) = default;
    std::string Event() const;
    std::string Floor() const;
    std::string Room() const;

private:
    std::string m_event;
    std::string m_floor;
    std::string m_room; 
};   
  
}//sh

#endif //SMART_HOME_SUBSCRIBE_DETAILS_HPP

