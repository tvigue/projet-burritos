#include "syscall.h"

// test du ForkExec :
// création de 5 processus qui créés 6 threads chacuns

int main(){
	int i;
	for(i=0;i<5;i++){
		ForkExec("build/threads");
	}
	for(i=0;i<1000;i++);
	PutString("\n");	
	Exit(0);
}
