#ifndef SMART_HOME_SAA_KEY_HPP
#define SMART_HOME_SAA_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class SAA_key : public Key {
public:
    SAA_key(int a_type, const std::string& a_event);
    // ~SAA_key() = default;

    // int Type() const;
    bool operator<(const SAA_key& a_other) const;
    // SAA_key& operator=(const SAA_key& a_other) = default;
    // SAA_key(const SAA_key& a_other) = default;

private:
    const std::string m_event;
};

} //sh

#endif //SMART_HOME_SAA_KEY_HPP

