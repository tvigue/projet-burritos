#ifdef CHANGED
#ifndef ARGUMENT_H
#define ARGUMENT_H

class Argument
{

public:
    Argument (int f,int arg);	
    ~Argument ();
    int getFunction();
    int getArgs();
private :
    int function;
    int args;

};
#endif
#endif //CHANGED
