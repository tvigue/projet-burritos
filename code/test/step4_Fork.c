#include "syscall.h"

int main()
{
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	Exit(0);
	
}
