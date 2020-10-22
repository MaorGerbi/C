#ifndef SMART_HOME_EVENT_H
#define SMART_HOME_EVENT_H

#include <string>
#include <time.h>
#include <iostream>
#include <tr1/memory>

namespace sh {

class Event {
public:
	typedef std::tr1::shared_ptr<Event> EventPtr;
	
public:
	Event(std::string a_type, std::string a_data, std::string a_location);
	//~Evvent() = default 
	
	const std::string& Type() const;
	const std::string& Data() const;
	const std::string& TimeStamp() const;
	const std::string& Location() const;
	bool operator==(const Event& a_other) const;

private:
	std::string getCurrentTime();
		
private:
	std::string m_type;
	std::string m_data;
	std::string m_location;
	std::string m_timeStamp;
	static const size_t timeStringLength = 200;
};

} //sh

#endif //SMART_HOME_EVENT_H

