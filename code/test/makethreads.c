#include "syscall.h"

void function (void * a){
	PutString("coucou je suis le thread 1\n");
	PutChar('\n');
}

int main(){
	//int i;
	int arg=5;
	UserThreadCreate(function,&arg);
	PutChar('E');
	PutChar('\n');
	PutString("salut ça va\n");
	Exit(0);
}
