#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <iostream>
#include "thread.hpp"

int counter; 
pthread_mutex_t lock; 

void foo() {
	std::cout << "thread -----------\n";
}

void* Race() 
{ 
	size_t i = 0; 
	int stackCounter = 0;
	for (i = 0; i < 100000; i++)
	{
	    //pthread_mutex_lock(&lock); 
		counter +=1;
		//pthread_mutex_unlock(&lock);
		stackCounter += 1; 
	} 
    printf("end job \n");
    printf("the value of counter on stack is: %d \n",stackCounter);
    //foo();
	return NULL;
	 
} 


struct MyRoutine : public experis::Routine {
	virtual void RunFunction() {
		Race();
	}
};


int main(void) 
{ 
    if (pthread_mutex_init(&lock, NULL) != 0)
    { 
		printf("\n mutex init has failed\n"); 
		return 1; 
    } 
    {
    	MyRoutine r1;
		experis::Thread thread1(r1);
		experis::Thread thread2(r1);
		foo();
		std::cout << "hi from main\n";
		thread1.Join();
		thread2.Join();
	}

	pthread_mutex_destroy(&lock); 
	printf("the value of counter is: %d while expect 2000000000\n",counter);
	return 0; 
} 
