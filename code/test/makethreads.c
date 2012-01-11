#include "syscall.h"

void function (void * a){
	//int i;
	//for(i=0;i<100;i++)
	char* s = "..........";
	GetString(s,10);
	PutString(s);
	PutChar('\n');
	UserThreadExit();
}

int main(){
	char f;
	//int i;
	int arg=5;
	UserThreadCreate(function,&arg);
	PutChar('E');
	PutChar('\n');
	//WaitUserThread();
	PutString("salut ça va\n");
	f = GetChar();
	PutChar(f);
	Halt();
}
