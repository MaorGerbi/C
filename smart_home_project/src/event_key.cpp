#include "event_key.hpp"

namespace sh {

EventKey::EventKey(const std::string& a_event, const std::string& a_floor, const std::string& a_room) 
: m_event(a_event)
, m_floor(std::stoi(a_floor))
, m_room(std::stoi(a_room))
{
}

bool EventKey::operator<(const EventKey& a_other) const {
    if (m_event.compare(m_event) < 0) {
        return true;
    }
    else if (m_event.compare(m_event) > 0) {
        return false;
    }
    else if (m_floor < a_other.m_floor) { //event are equals
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

