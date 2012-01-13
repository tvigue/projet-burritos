#include "syscall.h"

//a contient un seul argument
void function (void * a){
	PutString((char *)a);
	UserThreadExit();
}

//a contient plusieus arguments de types differents
void function2 (void * a){
	PutString((char*)(((void**)a)[0]));
	PutInt((int)(((void**)a)[1]));
	UserThreadExit();
}

int main(){
	char * arg2="Super";
	void * arg[2];
	arg[0]=(void *)"Cool";
	arg[1]=(void *)10;
	UserThreadCreate(function2,arg);
	UserThreadCreate(function,(void *)arg2);
	UserThreadWait();
	Exit(0);
}
