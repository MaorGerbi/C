#ifndef SMART_HOME_KEY_PROTOCOL_HPP
#define SMART_HOME_KEY_PROTOCOL_HPP

#include <memory>
#include <vector>
#include "uncopyable.hpp"
#include "subscribe_details.hpp"
#include "key.hpp"
#include "aaa_key.hpp"
#include "aas_key.hpp"
#include "ass_key.hpp"
#include "saa_key.hpp"
#include "sas_key.hpp"
#include "sss_key.hpp"

namespace sh {

class KeyProtocol : private experis::Uncopyable {
public:
    typedef std::shared_ptr<Key> KeyPtr;
    typedef std::shared_ptr <sh::SubscribeDetails>  SubscribeDetailsPtr;

public:
    //KeyProtocol() = default;
    //~KeyProtocol() = default;

    KeyPtr ConvertToKey(SubscribeDetails a_subDetails) const;
    std::vector<KeyPtr> GetKeys(SubscribeDetails a_eventInfo) const ;
};

}//sh

#endif //SMART_HOME_KEY_PROTOCOL_HPP
