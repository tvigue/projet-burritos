#include "syscall.h"

//test du GetChar
//L'appel à PutChar sert à vérifier celui du GetChar.

int main(){
	char c = GetChar();
	PutChar(c);
	PutChar('\n');
	return 0;
}
