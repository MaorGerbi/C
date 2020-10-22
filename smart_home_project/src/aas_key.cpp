#include "aas_key.hpp"

namespace sh {

AAS_key::AAS_key(int a_type, const std::string& a_room) 
: Key(a_type)
, m_room(std::stoi(a_room))
{
}

bool AAS_key::operator<(const AAS_key& a_other) const {
 if (m_room < a_other.m_room) { 
        return true;
    }
    return false;
}

} // sh

