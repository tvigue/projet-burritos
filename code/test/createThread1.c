#include "syscall.h"

void function (void * a){
	PutString("salut sa va\n");
	UserThreadExit();
}

int main(){

	int arg=5;
	UserThreadCreate(function,&arg);
	WaitUserThread();
	Exit(0);
}
