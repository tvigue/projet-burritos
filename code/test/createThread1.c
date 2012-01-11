#include "syscall.h"

void function (void * a){
	PutChar('!');
	UserThreadExit();
}

int main(){
	int arg=5;
	int i;//,j=0;
	for(i=0;i<100;i++){
		UserThreadCreate(function,&arg);
	}
	WaitUserThread();
	Exit(0);
}
