#include "syscall.h"

int main()
{
	ForkExec("build/putstring");
	ForkExec("build/putchar");
	int i;
	for(i=0;i<100000000;i++);
	Exit(0);
	
}
