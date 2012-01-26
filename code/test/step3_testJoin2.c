#include "syscall.h"

// test du UserThreadJoin

int thID;
int arg=0;

void function6(void * a){
	arg++;
	PutString("thread n ");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function5(void * a){
	arg++;
	thID=UserThreadCreate(function6,(void *)arg);
	UserThreadJoin(thID);
	PutString("thread n ");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function4(void * a){
	arg++;
	thID=UserThreadCreate(function5,(void *)arg);
	UserThreadJoin(thID);
	PutString("thread n ");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function3(void * a){
	arg++;
	thID=UserThreadCreate(function4,(void *)arg);
	UserThreadJoin(thID);
	PutString("thread n ");
	PutInt((int) a);
	PutString(" fini!\n");
}

int main(){
	
	PutString("test2:\n");
	PutString("Chaque thread créé attend le suivant:\n");
	arg=0;
	UserThreadCreate(function3,(void *)arg);
	
	Exit(0);
}
