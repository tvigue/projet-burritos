#include "syscall.h"
int n,m,arg=5;
int T[99];
void function1(void * a){
	int i;
	for(i=0;i<100;i++)
		PutInt(i);
	UserThreadExit();
}

void function2(void * a){
	int i;
	for(i=0;i<100;i++)
		T[i]=UserThreadCreate(function1,&arg);
	
	PutInt(100);
	UserThreadExit();
}

int main(){
	m=UserThreadCreate(function2,&arg);
	UserThreadWait();
	PutString("lalala\n");
	Exit(0);
}
