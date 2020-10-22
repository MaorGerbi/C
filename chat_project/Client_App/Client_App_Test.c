#include "Client_App.h"

int main(void)
{
	Client* client;
	
	client = Client_Create();
	Client_Run(client);

	Client_Destroy(&client);

	return 0;	
}



