#ifndef SMART_HOME_SSS_KEY_HPP
#define SMART_HOME_SSS_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class SSS_key : public Key {
public:
    SSS_key(int a_type, const std::string& a_event, const std::string& a_floor, const std::string& a_room);
    // ~SSS_key() = default;

    // int Type() const;
    bool operator<(const SSS_key& a_other) const;
    // SSS_key& operator=(const SSS_key& a_other) = default;
    // SSS_key(const SSS_key& a_other) = default;

private:
    const std::string m_event;
    const int m_floor;
    const int m_room;
    //in m_type; 
};

} //sh

#endif //SMART_HOME_SSS_KEY_HPP

