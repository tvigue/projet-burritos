#include "syscall.h"

void function (void * a){
	//int i;
	//for(i=0;i<100;i++)
	PutChar('T');
	UserThreadExit();
}

int main(){
	//int i;
	int arg=5;
	UserThreadCreate(function,&arg);
	//for(i=0;i<1000;i++)
	PutChar('M');
	WaitUserThread();
	Halt();
}
