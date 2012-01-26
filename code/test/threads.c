#include "syscall.h"

//test qui créé 6 threads
//test utilisée pour le test2 du ForkExec

void function(void * a){
	int j;
	PutInt((int) a);
	for(j=0;j<1000;j++);
	
}

int main(){
	int i;
	int arg=0;
	for(i=0;i<6;i++){
		UserThreadCreate(function,(void *)arg);
		arg++;
	}
	Exit(0);
}
