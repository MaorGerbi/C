#include "is_arrived.hpp"

namespace sh {

IsArrived::IsArrived(bool& a_isArrived)
: m_isArrived(a_isArrived)
{
}

bool IsArrived::operator()() const { 
	return !m_isArrived;
}

} //sh

