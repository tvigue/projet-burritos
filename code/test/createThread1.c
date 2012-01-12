#include "syscall.h"
void function1(void * a){
	//UserThreadExit();
}

int main(){
	sem_t sem;
	int i;
	int j=3;
	j++;
	UserThreadCreate(function1,'\0');
	for(i='a';i<='z';i++)
		PutChar(i);
	Halt();
}
