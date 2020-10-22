#ifndef ROUTINE_H
#define ROUTINE_H

namespace experis {

struct Routine {
	//Routine(); = default
	virtual ~Routine(){}
	
	virtual void RunFunction() = 0;
	//RunFunction(const RunFunction& a_other); = default
	//RunFunction& operator=(const RunFunction& a_other); = default
};
	
} //experis

#endif // ROUTINE_H

