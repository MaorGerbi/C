#include "ass_key.hpp"

namespace sh {

ASS_key::ASS_key(int a_type, const std::string& a_floor, const std::string& a_room) 
: Key(a_type)
, m_floor(std::stoi(a_floor))
, m_room(std::stoi(a_room))
{
}

bool ASS_key::operator<(const ASS_key& a_other) const {
    if (m_floor < a_other.m_floor) { 
        return true;
    }
    else if (m_floor > a_other.m_floor) {
        return false;
    }
    else if (m_room < a_other.m_room) { //event&floor are equals
        return true;
    }
    return false;
}

} // sh

