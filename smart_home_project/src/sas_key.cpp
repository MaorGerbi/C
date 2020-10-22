#include "sas_key.hpp"

namespace sh {

SAS_key::SAS_key(int a_type, const std::string& a_event, const std::string& a_room) 
: Key(a_type)
, m_event(a_event)
, m_room(std::stoi(a_room))
{
}

bool SAS_key::operator<(const SAS_key& a_other) const {
    if (m_event.compare(a_other.m_event) < 0) {
        return true;
    }
    else if (m_event.compare(a_other.m_event) > 0) {
        return false;
    }
    else if (m_room < a_other.m_room) { //event&floor are equals
        return true;
    }
    return false;
}

} // sh

