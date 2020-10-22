#include "iostream"
#include "shared_pointer.hpp"
#include "demo.hpp"

void TestBasic() {
	bool isAlive = true;
	{
		experis::SharedPtr<experis::Demo> Ptr(new experis::Demo(&isAlive));
	}
	if (isAlive) {
	std::cout << "Fail" << std::endl;
	}
}

void TestNull() {
	{
		experis::SharedPtr<experis::Demo> Ptr(NULL);
	}
}

void TestOperatorAsterisk() {
	bool isAlive = true;
	experis::SharedPtr<experis::Demo> Ptr(new experis::Demo(&isAlive));
	if (!(*Ptr).GetStatus()) {
	std::cout << "Fail" << std::endl;
	}	
}

void TestOperatorArrow() {
	bool isAlive = true;
		experis::SharedPtr<experis::Demo> Ptr(new experis::Demo(&isAlive));
	if (!(Ptr->GetStatus())) {
	std::cout << "Fail" << std::endl;
	}
}	
	/*
void TestCopyCtor() {
    bool isAlive = true;
    {
		experis::SharedPtr<experis::Demo> Ptr(new experis::Demo(&isAlive));
		{
			experis::SharedPtr<experis::Demo> Ptr1(Ptr);
		}
		if (Ptr1
	}
}*/
	
int main () {

	TestBasic();
	TestNull();
	//TestCopyCtor();
	TestOperatorAsterisk();
	TestOperatorArrow();

	return 0;
}
