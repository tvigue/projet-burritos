#include "syscall.h"

// test du UserThreadJoin

// Dans ce test il n'y a plus d'appel à UserThreadExit()
// ni l'appel à UserThreadWait()

int n;
int arg=0;
int T[10];

void function2(void * a){
	PutString("Je suis le thread n°");
	PutInt((int) a);
}	

// fonction qui fait un join sur plusieurs autres threads
void function1(void * a){
	int i;
	PutString("Je suis le thread n°");
	PutInt((int) a);
	for(i=0;i<10;i++){
		arg++;
		n=UserThreadCreate(function2,(void *)arg);
		T[i]=n;
	}
	for(i=0;i<10;i++){
		if(T[i]!=-1){
			UserThreadJoin(T[i]);
		}
	}
	PutString("fin fonction 1\n");
}

void function6(void * a){
	arg++;
	PutString("thread n°");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function5(void * a){
	arg++;
	n=UserThreadCreate(function6,(void *)arg);
	UserThreadJoin(n);
	PutString("thread n°");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function4(void * a){
	arg++;
	n=UserThreadCreate(function5,(void *)arg);
	UserThreadJoin(n);
	PutString("thread n°");
	PutInt((int) a);
	PutString(" fini!\n");
}

//fonction qui creee un thread et l'attend
void function3(void * a){
	arg++;
	n=UserThreadCreate(function4,(void *)arg);
	UserThreadJoin(n);
	PutString("thread n°");
	PutInt((int) a);
	PutString(" fini!\n");
}

int main(){
	PutString("test1:\n");
	PutString("creation d'un thread qui en attend plusieurs :\n");
	UserThreadCreate(function1,(void *)arg);
	UserThreadWait();
	PutString("fin du test1\n");
	
	PutString("test2:\n");
	PutString("Chaque thread cree attend le suivan :t\n");
	arg=0;
	
	UserThreadCreate(function3,(void *)arg);
	
	Exit(0);
}
