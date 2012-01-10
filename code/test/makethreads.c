#include "syscall.h"

void function (void * a){
	PutString("###########################");
	PutChar('\n');
	UserThreadExit();
}

int main(){

	int arg=5;
	UserThreadCreate(function,&arg);
	PutString("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	PutChar('c');
	PutString(".........");
	WaitUserThread();
	Exit(0);
}
