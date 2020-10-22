#ifndef __DEMO__
#define __DEMO__

namespace experis {
class Demo { 
public:
	Demo(bool* a_isAlive);
	~Demo();
	bool GetStatus() const { return * m_isAlive;}
	
private:
	bool* m_isAlive;
};

Demo::Demo(bool* a_isAlive)
: m_isAlive(a_isAlive) {
}

Demo::~Demo() {
	*m_isAlive = false;
}

} //experis

#endif //__DEMO__
