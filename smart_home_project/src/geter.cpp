#include "geter.hpp"

namespace sh {

Geter::Geter(const EventLut& a_lut)
: m_lut(a_lut)
{
}

std::vector<Geter::EventHandlerPtr> Geter::Get(SubscribeDetailsPtr a_detail) const {
     return m_lut.Search(a_detail);
 }
 
}//sh