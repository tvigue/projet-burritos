#include "syscall.h"

void function (void * a){
	int i;
	for(i=0;i<100;i++)
	PutChar('T');
	UserThreadExit();
}

int main(){

	int arg=5;
	int i;
	UserThreadCreate(function,&arg);
	for(i=0;i<100;i++)
	PutChar('M');
	
	WaitUserThread();
	Exit(0);
}
