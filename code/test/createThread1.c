#include "syscall.h"
/*void function2(void * a){
	PutString((char*)(((void**)a)[0]));
	PutInt((int)(((void**)a)[1]));
	PutString("Fin Thread 2\n");
}


void function1(void * a){
	int n=UserThreadCreate(function2,a);
	PutInt(n);
	UserThreadJoin(n);
	PutString("Fin Thread\n");
}
*/

int main(){
	/*void * arg[2];
	arg[0]=(void *)"Cool";
	arg[1]=(void *)10;
	UserThreadCreate(function1,arg);
	*/
	PutInt(12);
	Exit(0);
}
