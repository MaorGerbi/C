#ifndef SMART_HOME_IS_ARRIVED_H
#define SMART_HOME_IS_ARRIVED_H

namespace sh {
 
class IsArrived {
public:
	IsArrived(bool& a_isArrived);
	bool operator()() const;
	
private:
	bool& m_isArrived;
};

} //sh

#endif // SMART_HOME_IS_ARRIVED_H

