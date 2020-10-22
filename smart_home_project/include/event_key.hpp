#ifndef SMART_HOME_EVENT_KEY_HPP
#define SMART_HOME_EVENT_KEY_HPP

#include <string>
#include <iostream>

namespace sh {

class EventKey {
public:
    EventKey(const std::string& a_event, const std::string& a_floor, const std::string& a_room);
    // ~EventKey() = default;

    bool operator<(const EventKey& a_other) const;
    // EventKey& operator=(const EventKey& a_other) = default;
    // EventKey(const EventKey& a_other) = default;

private:
    const std::string m_event;
    const int m_floor;
    const int m_room;
};

} //sh

#endif //SMART_HOME_EVENT_KEY_HPP

