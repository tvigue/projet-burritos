#include "syscall.h"

//a contient plusieus arguments de types differents
void function1 (void * a){
	PutString((char*)(((void**)a)[0]));
	PutInt((int)(((void**)a)[1]));
}

//a contient un seul argument
void function2 (void * a){
	PutString((char *)a);
}

int main(){
	void * arg[2];
	char * arg2;
	arg[0]=(void *)"thread";
	arg[1]=(void *)1;
	arg2="thread2";
	UserThreadCreate(function1,arg);
	UserThreadCreate(function2,(void *)arg2);
	Exit(0);
}
