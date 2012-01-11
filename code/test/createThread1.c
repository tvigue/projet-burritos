#include "syscall.h"

void function (void * a){
	PutString("Vos gueules\n");
	UserThreadExit();
}

int main(){

	int arg=5;
	UserThreadCreate(function,&arg);
	UserThreadCreate(function,&arg);
	WaitUserThread();
	Exit(0);
}
