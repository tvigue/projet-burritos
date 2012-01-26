#include "syscall.h"

//test du GetString
//L'appel à PutString sert à vérifier celui du GetString.

int main ()
{
	char* s = "";
	int n = 0;
	GetString(s,n);
	PutString(s);
	PutChar('\n');
	return 0;
}
