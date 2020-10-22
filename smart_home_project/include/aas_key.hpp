#ifndef SMART_HOME_AAS_KEY_HPP
#define SMART_HOME_AAS_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class AAS_key : public Key {
public:
    AAS_key(int a_type, const std::string& a_room);
    // ~AAS_key() = default;

    // int Type() const;
    bool operator<(const AAS_key& a_other) const;
    // AAS_key& operator=(const AAS_key& a_other) = default;
    // AAS_key(const AAS_key& a_other) = default;

private:
    const int m_room;
};

} //sh

#endif //SMART_HOME_AAS_KEY_HPP

