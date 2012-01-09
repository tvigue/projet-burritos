#include "syscall.h"

void function (void * a){

	PutString("Bonjour je suis roumain!!");

}

int main(){

	int arg=5;
	UserThreadCreate(function,&arg);

	return 1;
}
