#include "event_lut.hpp"

namespace sh {

EventLut::EventLut()
: m_eventsLut_aaa()
, m_eventsLut_aas()
, m_eventsLut_ass()
, m_eventsLut_saa()                      
, m_eventsLut_sas()
, m_eventsLut_sss()
, m_protocol()
{
}

EventLut::Value EventLut::Search(LutKey a_key) const { 
    static const int searchCycle = 6;
    Value requestRes;
    std::vector<KeyPtr> keysContainer = m_protocol.GetKeys(*a_key);

    for (int i = 0; i <= searchCycle; ++i) {
        switch(i) {
        case 0 : {
            Value vecToAppend;
            requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            break;
        }
        case 1: {
            std::shared_ptr<sh::AAS_key> key2 = std::dynamic_pointer_cast<sh::AAS_key>(keysContainer[i]);
            if (m_eventsLut_aas.find(*key2)!= m_eventsLut_aas.end()) {
                Value vecToAppend = m_eventsLut_aas.find(*key2)->second;
                requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            }
            break;
        }
        case 2: {
            std::shared_ptr<sh::ASS_key> key3 = std::dynamic_pointer_cast<sh::ASS_key>(keysContainer[i]);
            if (m_eventsLut_ass.find(*key3) != m_eventsLut_ass.end()) {
                Value vecToAppend  = m_eventsLut_ass.find(*key3)->second;
                requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            }
            break;
        }
        case 3: {
            std::shared_ptr<sh::SAA_key> key4 = std::dynamic_pointer_cast<sh::SAA_key>(keysContainer[i]);
            if (m_eventsLut_saa.find(*key4) != m_eventsLut_saa.end()) {
                Value vecToAppend  = m_eventsLut_saa.find(*key4)->second;
                requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            }
            break;
        }
        case 4: {
            std::shared_ptr<sh::SAS_key> key5 = std::dynamic_pointer_cast<sh::SAS_key>(keysContainer[i]);
            //appendResVector(key, reqRe)   accumulatEventHandlers()
            if (m_eventsLut_sas.find(*key5) != m_eventsLut_sas.end()) {
                Value vecToAppend  = m_eventsLut_sas.find(*key5)->second;
                requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            }
            break;
        }
        case 5: {
            std::shared_ptr<sh::SSS_key> key6 = std::dynamic_pointer_cast<sh::SSS_key>(keysContainer[i]);
            if (m_eventsLut_sss.find(*key6) != m_eventsLut_sss.end()) {
                Value vecToAppend  = m_eventsLut_sss.find(*key6)->second;
                requestRes.insert(requestRes.end(), vecToAppend.begin(), vecToAppend.end());
            }
            break;
        } 
        } //switch
    } //if
    return requestRes;
}

void EventLut::Add(LutKey a_key, EventHandlerPtr a_value) {
    KeyPtr key = m_protocol.ConvertToKey(*a_key);
    int keyType = key->Type();

    switch(keyType)
    {
    case 1:
        m_eventsLut_aaa.push_back(a_value);
        break;
    case 2: {
        std::shared_ptr<sh::AAS_key> key2 = std::dynamic_pointer_cast<sh::AAS_key>(key);
        m_eventsLut_aas[*key2].push_back(a_value);
        break;
    }
    case 3: { 
        std::shared_ptr<sh::ASS_key> key3 = std::dynamic_pointer_cast<sh::ASS_key>(key);
        m_eventsLut_ass[*key3].push_back(a_value);
        break;
    }
    case 4: {
        std::shared_ptr<sh::SAA_key> key4 =  std::dynamic_pointer_cast<sh::SAA_key>(key);
        m_eventsLut_saa[*key4].push_back(a_value);
        break; 
    }
    case 5: {
        std::shared_ptr<sh::SAS_key> key5 =  std::dynamic_pointer_cast<sh::SAS_key>(key);
        m_eventsLut_sas[*key5].push_back(a_value);
        break; 
    }    
    case 6: {
        std::shared_ptr<sh::SSS_key> key6 =  std::dynamic_pointer_cast<sh::SSS_key>(key);
        m_eventsLut_sss[*key6].push_back(a_value);
        break;
    }
    }
}

size_t EventLut::Size() const {
    return m_eventsLut_aaa.size() + m_eventsLut_aas.size() +
           m_eventsLut_saa.size() + m_eventsLut_sas.size() +
           m_eventsLut_sss.size() + m_eventsLut_aas.size() ;
}

} //sh


//allevent,allfloars,allrooms - key 1 -AAA_key V 
//allevent, allfloars, sps    - key 2 -AAS_key V
//all event, spsfic, spsific  - key 3  ASS_key V -V

//sp , all, all                -key 4  SAA_key V -V
//sps, all ,sps                -key 5  SAS_key V -V
//sp , sp, sp                  -key 6 SSS_key  V- V


