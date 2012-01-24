#include "syscall.h"

int main()
{
	int i;
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	for(i=0;i<100000;i++){}
	PutString("BBBBBBB\n");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	Exit(0);
	
}
