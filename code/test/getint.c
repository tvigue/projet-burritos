#include "syscall.h"

//test GetInt
//L'appel à PutInt sert à vérifier celui du GetInt

int main(){
	int i;
	GetInt(&i);
	PutInt(i);
	PutChar('\n');
	return 0;
}
