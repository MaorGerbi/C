#include "extract_handle.hpp"

namespace sh{

ExtractorHandle::ExtractorHandle(const Geter& a_geter, Dequeuer& a_deqer)
: m_geter(a_geter)
, m_deqer(a_deqer)
{
}

Event::EventPtr ExtractorHandle::GetCurrentEvent() const {
    Event::EventPtr Qitem;
    m_deqer.Dequeue(Qitem);
    return Qitem;
}

std::vector<ExtractorHandle::EventHandlerPtr> ExtractorHandle::BringNewHandlers(Event::EventPtr a_Key) const {
    SubscribeDetailsPtr eventToRegistr(new SubscribeDetails(a_Key->Type(),"1","1"));
    return m_geter.Get(eventToRegistr);
}

} //sh
