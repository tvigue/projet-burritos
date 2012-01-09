#include "syscall.h"

void function (int a){

	PutString("Bonjour je suis roumain!!");

}

int main(){


	UserThreadCreate(function,5);


}
