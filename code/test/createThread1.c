#include "syscall.h"

void function (void * a){
	PutString("Vos gueules\n");
	UserThreadExit();
}

int main(){

	int * arg=0;
	int s=10;
	int g=4;
	arg[0]=(int)&s;
	arg[1]=(int)&g;
	UserThreadCreate(function,&s);
	WaitUserThread();
	Exit(0);
}
