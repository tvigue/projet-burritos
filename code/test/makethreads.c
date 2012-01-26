#include "syscall.h"

void function (void * a){
	PutString("je suis le thread crée!\n");
	PutChar('\n');
}

int main(){
	int arg=5;
	UserThreadCreate(function,&arg);
	PutString("fin du test makethreads\n");
	Exit(0);
}
