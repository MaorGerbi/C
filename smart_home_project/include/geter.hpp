#ifndef SMART_HOME_GETER_HPP
#define SMART_HOME_GETTE_HPP

#include <tr1/memory>
#include <vector>
#include "event_lut.hpp"
#include "uncopyable.hpp"
#include "subscribe_details.hpp"
#include "event_lut.hpp"

namespace sh {

class Geter: private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;
    typedef std::tr1::shared_ptr<SubscribeDetails> SubscribeDetailsPtr;

public:
    Geter(const EventLut& a_lut);
    // ~Geter() = default;

    std::vector<EventHandlerPtr> Get(SubscribeDetailsPtr a_detail) const;

private:
    const EventLut& m_lut;
};

} //sh

#endif //SMART_HOME_GETER