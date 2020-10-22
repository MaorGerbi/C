#include <stdio.h>
#include <unistd.h>
#include "Multicast.h"

int main()
{
	MulticastCreate("225.1.1.1", 1234, "ziv","ziv");
	MulticastCreate("226.1.1.1", 1234, "not", "not");
	sleep(3);
	MulticastDestroy("ziv","ziv");

	sleep(3);
	MulticastDestroy("not", "not");
	return 0;
}
