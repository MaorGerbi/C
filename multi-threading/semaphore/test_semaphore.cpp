#include <stdio.h>
#include "semaphore.hpp"

pthread_t tid[2]; 
int counter; 
experis::Semaphore sem(experis::Semaphore::THREAD, 1);
void* Race(void* arg) 
{ 
	size_t i = 0; 
	int stackCounter = 0;
	for (i = 0; i < 1000000000; i++)
	{
	    sem.Wait();
		counter += 1;
		sem.Notify();
		stackCounter += 1; 
	} 
    printf("end job \n");
    printf("the value of counter on stack is: %d \n",stackCounter);
	return NULL; 
} 

int main(void) 
{ 
	int i = 0; 
	int error; 
	 
	while (i < 2)
    { 
		error = pthread_create(&(tid[i]), NULL, &Race, NULL); 
		if (error != 0)
		{
		//	printf("\nThread can't be created : [%s] \n", strerror(error)); 
		}
		++i; 
	} 
	
	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	
	printf("the value of counter is: %d while expect 2000000000\n",counter);
	return 0; 
} 

