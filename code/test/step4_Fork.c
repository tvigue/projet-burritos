#include "syscall.h"

int main()
{
	ForkExec("build/step3_testJoin2");
	ForkExec("build/putstring");
	Exit(0);
	
}
