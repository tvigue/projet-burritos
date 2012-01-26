#include "syscall.h"

// test du UserThreadJoin

int ThID;
int arg=0;
int T[10];

void function2(void * a){
	PutString("Je suis le thread n ");
	PutInt((int) a);
}	

// fonction qui fait un join sur plusieurs autres threads
void function1(void * a){
	int i;
	PutString("Je suis le thread n ");
	PutInt((int) a);
	for(i=0;i<10;i++){
		arg++;
		ThID=UserThreadCreate(function2,(void *)arg);
		T[i]=ThID;
	}
	for(i=0;i<10;i++){
		if(T[i]!=-1){
			UserThreadJoin(T[i]);
		}
	}
	PutString("\n");
	PutString("fin fonction 1\n");
}

int main(){
	PutString("test1:\n");
	PutString("création d'un thread");
	PutString(" qui va en attendre plusieurs:\n");
	ThID=UserThreadCreate(function1,(void *)arg);
	UserThreadJoin(ThID);
	PutString("fin du testJoin1\n");
	
	Exit(0);
}
