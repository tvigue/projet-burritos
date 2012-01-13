#include "syscall.h"

void f1(void * arg){
	int i;
	
	for(i=0;i<1000;i++){
		PutInt(1);
	}
}

void f2(void * arg){
	int i;

	for(i=0;i<1000;i++){
		PutInt(2);
	}
}

int main(){
	int a1 = 1;
	int a2 = 2;
	int n,m;
	n = UserThreadCreate(f1,&a1);
	m = UserThreadCreate(f2,&a2);
	
	Exit(0);

}
