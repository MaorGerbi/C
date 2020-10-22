#ifndef SMART_HOME_COMPARE_HPP
#define SMART_HOME_COMPARE_HPP

#include "event_key.hpp"

namespace sh {

struct Compare {
    bool operator()(const EventKey& a_first, const EventKey& a_second);
};

} //sh

#endif //SMART_HOME_COMPARE_HPP
