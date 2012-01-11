#include "syscall.h"

void function (void * a){
	PutChar('a');
	UserThreadExit();
}

int main(){

	int arg=5;
	int i;
	for(i=0;i<10;i++){
		UserThreadCreate(function,&arg);
	}
	WaitUserThread();
	Exit(0);
}
