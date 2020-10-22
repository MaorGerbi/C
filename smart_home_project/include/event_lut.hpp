#ifndef SMART_HOME_EVENT_LUT_HPP
#define SMART_HOME_EVENT_LUT_HPP

#include <memory>
#include <map>
#include <utility>
#include <vector>
#include "uncopyable.hpp"
#include "event_key.hpp"
#include "event_handler.hpp"
#include "subscribe_details.hpp"

#include "key_protocol.hpp"
#include "ass_key.hpp"

namespace sh{

class EventLut : private experis::Uncopyable {
public:
    typedef std::tr1::shared_ptr<EventHandler> EventHandlerPtr;
    typedef std::tr1::shared_ptr<SubscribeDetails> SubscribeDetailsPtr;
    typedef std::shared_ptr<Key> KeyPtr;
    typedef std::vector <EventHandlerPtr> Value;
    typedef SubscribeDetailsPtr LutKey;

public:
     EventLut();
    //~EventLut() = default;

    Value Search(LutKey a_key) const;
    void Add(LutKey a_key, EventHandlerPtr a_value);
    size_t Size() const;

private:
    std::vector <EventHandlerPtr> m_eventsLut_aaa;
    std::map <AAS_key, Value> m_eventsLut_aas; 
    std::map <ASS_key, Value> m_eventsLut_ass;
    std::map <SAA_key, Value> m_eventsLut_saa;
    std::map <SAS_key, Value> m_eventsLut_sas; 
    std::map <SSS_key, Value> m_eventsLut_sss;
    KeyProtocol m_protocol;
};

} //sh

#endif //SMART_HOME_EVENT_LUT_HPP

