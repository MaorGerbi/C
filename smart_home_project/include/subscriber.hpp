#ifndef SMART_HOME_SUBSCRIBER_HPP
#define SMART_HOME_SUBSCRIBER_HPP

#include <tr1/memory>
#include "event_lut.hpp"
#include "uncopyable.hpp"
#include "event_handler.hpp"
#include "event_key.hpp"
#include "subscribe_details.hpp"

namespace sh {

class Subscriber : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;
    typedef std::tr1::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;

public:
    Subscriber(EventLut& a_lut);
    //~Subscriber() = default;

    void Subscribe(EventHandlerPtr a_controller, SubscribeDetailsPtr a_subInfo);

private:
    EventLut& m_lut;
};

} //sh

#endif //SMART_HOME_SUBSCRIBER_HPP

