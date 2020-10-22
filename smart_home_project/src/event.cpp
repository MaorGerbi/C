#include "event.hpp"

namespace sh {

Event::Event(std::string a_type, std::string a_data, std::string a_location)
: m_type(a_type)
, m_data(a_data)
, m_location(a_location) 
{
	m_timeStamp = getCurrentTime();
}

const std::string& Event::TimeStamp() const {
	return m_timeStamp; 
}

const std::string& Event::Type() const { 
	return m_type; 
}

const std::string& Event::Data() const { 
	return m_data; 
}

const std::string& Event::Location() const { 
	return m_location; 
}
     //bool operator==(const Event& a_other) const;
bool Event::operator==(const Event& a_other) const{
	return (m_timeStamp == a_other.m_timeStamp)&&(m_type == a_other.m_type)&&(m_data == a_other.m_data)&&(m_location ==a_other.m_location);
	
}

std::string Event::getCurrentTime() {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	char timeBuff[timeStringLength];
	strftime(timeBuff, sizeof timeBuff, "%D %T ", gmtime(&ts.tv_sec));
	return timeBuff;
}

} //sh
