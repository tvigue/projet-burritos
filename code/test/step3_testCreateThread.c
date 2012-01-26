#include "syscall.h"

int arg;
	
//fonction qui affiche le numéro de la création du thread
void function1(void * a){
	PutString("Je suis le thread n");
	PutInt((int) a);
}

// fonction qui créé 100 thread
void function2(void * a){
	int i;
	for(i=0;i<100;i++){
		arg = i;
		UserThreadCreate(function1,(void *)arg);
	}
}

int main(){
	UserThreadCreate(function2,(void *)arg);
	Exit(0);
}
