#include "syscall.h"

void function (void * a){
	PutString((char *)a);
}

void function2 (void * a){
	PutString((char*)(((void**)a)[0]));
	PutInt((int)(((void**)a)[1]));
}

int main(){
	char * arg2="Nachos";
	void * arg[2];
	arg[0]=(void *)"Projet";
	arg[1]=(void *)10;
	UserThreadCreate(function2,arg);
	UserThreadCreate(function,(void *)arg2);
	UserThreadWait();
	Exit(0);
}
