#ifndef SMART_HOME_AGENT_DETAILS
#define SMART_HOME_AGENT_DETAILS

#include <string>
#include <iostream>

namespace sh {

class AgentDetails {
public:
	AgentDetails(std::string a_id, std::string a_type, std::string a_location, std::string a_configData);
	//~AgentDEtails(); = default
	
	//AgentDEtails(const AgentDEtails& a_agent); = default
	//AgentDEtails& operator=(const AgentDEtails& a_agent); = default
	 
	const std::string& Id() const;
	const std::string& Type() const;
    const std::string& Loction() const;
    const std::string& ConfigData() const;

private:
	std::string m_id; 
	std::string m_type;
	std::string m_location;
	std::string m_configData;
};

} //sh

#endif //AgentDetails
