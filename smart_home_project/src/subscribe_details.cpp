#include "subscribe_details.hpp"

namespace sh { 

SubscribeDetails::SubscribeDetails(std::string a_event, std::string a_floor, std::string a_room)
: m_event(a_event)
, m_floor(a_floor)
, m_room(a_room)
{
}

std::string SubscribeDetails::Event() const {
    return m_event;
}

std::string SubscribeDetails::Floor() const {
    return m_floor;
}

std::string SubscribeDetails::Room() const {
    return m_room;
}

}// sh

