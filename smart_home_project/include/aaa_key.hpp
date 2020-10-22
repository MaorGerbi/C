#ifndef SMART_HOME_AAA_KEY_HPP
#define SMART_HOME_AAA_KEY_HPP

#include <string>
#include <iostream>
#include "key.hpp"

namespace sh {

class AAA_key : public Key {
public:
    AAA_key(int a_type);
    // ~AAA_key() = default;

    // AAA_key& operator=(const AAA_key& a_other) = default;
    // AAA_key(const AAA_key& a_other) = default;

private:
    int m_type;
};

} //sh

#endif //SMART_HOME_AAA_KEY_HPP
