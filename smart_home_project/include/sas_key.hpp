#ifndef SMART_HOME_SAS_KEY_HPP
#define SMART_HOME_SAS_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class SAS_key : public Key {
public:
    SAS_key(int a_type, const std::string& a_event, const std::string& a_room);
    // ~SAS_key() = default;

    // int Type() const;
    bool operator<(const SAS_key& a_other) const;
    // SAS_key& operator=(const SAS_key& a_other) = default;
    // SAS_key(const SAS_key& a_other) = default;

private:
    const std::string m_event;
    const int m_room;
};

} //sh

#endif//SMART_HOME_SAS_KEY_HPP

