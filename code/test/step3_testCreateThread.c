#include "syscall.h"

int T[99];
int arg;

//fonction qui affiche le numéro de la création du thread
void function1(void * a){
	PutString("Je suis le thread n°");
	PutInt((int) a);
	UserThreadExit();
}

// fonction qui créé 100 thread
void function2(void * a){
	int i;
	for(i=0;i<100;i++){
		arg = i;
		T[i]=UserThreadCreate(function1,(void *)arg);
	}
	UserThreadExit();
}

int main(){
	UserThreadCreate(function2,(void *)arg);
	int j;
	for(j=0;j<1000;j++);
	arg=100;
	UserThreadCreate(function1,(void *)arg);
	UserThreadWait();
	PutString("fin du main\n");
	Exit(0);
}
