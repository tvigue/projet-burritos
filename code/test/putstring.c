#include "syscall.h"

//test du PutString

int main(){
	PutString("bienvenue en tp nachos\n");
	PutString("voici une super phrase qui est superbement trop longue et va donc se faire couper par l'appel a copy string from machine hhihihihihihih\n");
	Exit(0);
}
