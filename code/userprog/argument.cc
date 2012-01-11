
#include "argument.h"

Argument::Argument (int f,int arg){
	function=f;
	args=arg;
}

Argument::~Argument(){

}

int Argument::getFunction(){
	return function;

}

int Argument::getArgs(){
	return args;

}
