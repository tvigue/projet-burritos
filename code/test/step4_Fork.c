#include "syscall.h"

int main()
{
	int i;
	ForkExec("build/putstring");
	ForkExec("build/putstring");
	//ForkExec("build/putstring");
	for(i=0;i<10000;i++){}
	PutString("BBBBBBB\n");
	Exit(0);
	
}
