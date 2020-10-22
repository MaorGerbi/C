#include "key_protocol.hpp"

namespace sh {

KeyProtocol::KeyPtr KeyProtocol::ConvertToKey(SubscribeDetails a_subInfo) const {
    KeyPtr suitableKey;
    if (a_subInfo.Event().compare("all") == 0) {
        if (a_subInfo.Floor().compare("all") == 0 ) {
            if(a_subInfo.Room().compare("all") == 0) { //key1
                suitableKey =  KeyPtr(new AAA_key(1)); 
            }
            else {//key 2
                suitableKey = KeyPtr(new AAS_key(2, a_subInfo.Room()));
            }
        }
        else {//key 3
            suitableKey = KeyPtr(new ASS_key(3, a_subInfo.Floor(), a_subInfo.Room())); 
        }
    }
    else {
        if (a_subInfo.Floor().compare("all") == 0 ) {
            if (a_subInfo.Room().compare("all") == 0) {//key 4
                suitableKey = KeyPtr(new SAA_key(4, a_subInfo.Event()));
            }
            else {//key 5
                suitableKey = KeyPtr(new SAS_key(5, a_subInfo.Event(), a_subInfo.Room()));    
            }
        }
        else {//key 6
            suitableKey = KeyPtr(new SSS_key(6,a_subInfo.Event(),a_subInfo.Floor(), a_subInfo.Room()));
        }
    }    
    return suitableKey;
}

std::vector<KeyProtocol::KeyPtr> KeyProtocol::GetKeys(SubscribeDetails a_eventInfo) const {
    std::vector<KeyPtr> keysContainer;

    std::shared_ptr<AAA_key> aaa(new AAA_key(1));
    keysContainer.push_back(aaa); 

    std::shared_ptr<AAS_key> aas(new AAS_key(2, a_eventInfo.Room()));
    keysContainer.push_back(aas); 
    
    std::shared_ptr<ASS_key> ass(new ASS_key(3,a_eventInfo.Floor(), a_eventInfo.Room()));
    keysContainer.push_back(ass); 
    
    std::shared_ptr<SAA_key> saa(new SAA_key(4,a_eventInfo.Event()));
    keysContainer.push_back(saa); 
    
    std::shared_ptr<SAS_key> sas(new SAS_key(5,a_eventInfo.Event(), a_eventInfo.Room()));
    keysContainer.push_back(sas); 
    
    std::shared_ptr<SSS_key> sss(new SSS_key(6,a_eventInfo.Event(), a_eventInfo.Floor(), a_eventInfo.Room()));
    keysContainer.push_back(sss);
    
    return keysContainer;
}

} //sh

