#include "rendezvous.hpp"

namespace sh {

Rendezvous::Rendezvous() 
: m_mutex()
, m_cond() 
, m_isArrived(false)
{
}

void Rendezvous::Notifay() {
	experis::Guard g(m_mutex);
	m_isArrived = true;
    m_cond.Signal();
    assert(m_isArrived);
}

void Rendezvous::Wait() {
	experis::Guard g(m_mutex);
	if (m_isArrived) {
		return;
	} 
	IsArrived isArrived(m_isArrived);
	m_cond.Wait<IsArrived>(m_mutex, isArrived);
	assert(m_isArrived);
}

}// sh

