#include "syscall.h"

// test du UserThreadJoin

int thID;
int arg=0;

//fonction qui attend un thread créé dans le main
void function1(void * a){
	UserThreadJoin(thID);
	PutString("thread ");
	PutInt((int) a);
	PutString(" : le thread attendu et fini\n");
}

//thread qui est attendu
void function2(void * a){
	PutString("Je suis le thread n ");
	PutInt((int) a);
	PutString(", les autres threads m'attendent!\n");
}

int main(){
	
	PutString("test3:\n");
	PutString("Plusieurs threads créés attendent le meme:\n");
	arg=0;
	thID=UserThreadCreate(function2,(void *)arg);
	UserThreadCreate(function1,(void *)arg);
	UserThreadJoin(thID);
	PutString("le thread attendu est fini\n");
	PutString("fin test3\n");
	
	Exit(0);
}
