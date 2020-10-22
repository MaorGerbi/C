#include "saa_key.hpp"

namespace sh {

SAA_key::SAA_key(int a_type, const std::string& a_event) 
: Key(a_type)
, m_event(a_event)
{
}

bool SAA_key::operator<(const SAA_key& a_other) const {
    if (m_event.compare(a_other.m_event) < 0) {
        return true;
    }
    return false;
}

} // sh

