#include "agent_details.hpp" 

namespace sh {

AgentDetails::AgentDetails(std::string a_id, std::string a_type, std::string a_location,std::string a_configdata) 
: m_id(a_id)
, m_type(a_type)
, m_location(a_location)
, m_configData(a_configdata)
{
}

const std::string& AgentDetails::Id() const {
	return m_id;
}

const std::string& AgentDetails::Type() const {
	return m_type;
}

const std::string& AgentDetails::Loction() const {
	return m_location;
}

const std::string& AgentDetails::ConfigData() const {
	return m_configData;
}

} //sh

