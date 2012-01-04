#include "syscall.h"

int main(){
	PutString("bienvenue en tp nachos");
	PutChar('\n');
	PutString("voici une super phrase qui est superbement trop longue et va donc se faire couper par l'appel a copy string from machine hhihihihihihih");
	PutChar('\n');
	Exit(12);
}
