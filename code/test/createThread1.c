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
	
	for(i=0;i<100;i++)
		if(T[i]!=-1)
			UserThreadJoin(T[i]);
	PutInt(100);
	UserThreadExit();
}

int main(){
	m=UserThreadCreate(function2,&arg);
	UserThreadJoin(m);
	Exit(0);
}
