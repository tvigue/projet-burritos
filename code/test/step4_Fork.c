#include "syscall.h"

int main()
{
	int i;
	
	ForkExec("build/putstrg");
	for(i=0;i<100;i++){
		ForkExec("build/putchar");
	}
	Exit(0);
}
