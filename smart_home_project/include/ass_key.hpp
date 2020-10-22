#ifndef SMART_HOME_ASS_KEY_HPP
#define SMART_HOME_ASS_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class ASS_key : public Key {
public:
    ASS_key(int a_type, const std::string& a_floor, const std::string& a_room);
    // ~ASS_key() = default;

    // int Type() const;
    bool operator<(const ASS_key& a_other) const;
    // ASS_key& operator=(const ASS_key& a_other) = default;
    // ASS_key(const ASS_key& a_other) = default;

private:
    const int m_floor;
    const int m_room;
};

} //sh

#endif //SMART_HOME_ASS_KEY_HPP

