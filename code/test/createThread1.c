#include "syscall.h"

void function (void * a){
	PutString((char *)a);
	UserThreadExit();
}

int main(){
	char *arg="Cool";
	UserThreadCreate(function,(void *)arg);
	WaitUserThread();
	Exit(0);
}
