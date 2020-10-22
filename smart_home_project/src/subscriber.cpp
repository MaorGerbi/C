#include "subscriber.hpp"

namespace sh{

Subscriber::Subscriber(EventLut& a_lut)
: m_lut(a_lut)
{
}

void Subscriber::Subscribe(EventHandlerPtr a_controller, SubscribeDetailsPtr a_subInfo) {
    m_lut.Add(a_subInfo, a_controller);
}

} //sh
