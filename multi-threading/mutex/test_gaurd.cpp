
#include "guard.hpp"
#include "mutex.hpp"

int main(void)
{
	experis::Mutex m;
	experis::Guard G(m);
	return 0;
}
