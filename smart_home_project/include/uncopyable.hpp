#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

namespace experis {

class Uncopyable {

protected:
	Uncopyable(){}
	virtual ~Uncopyable(){}
	
private:
	Uncopyable (const Uncopyable& a_other); //fobidden
	Uncopyable& operator=(const Uncopyable& a_other); //forbidden
};

} //experis

#endif //UNCOPYABLE_H

