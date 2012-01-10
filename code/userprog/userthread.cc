#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

static int nbThread;

static void StartUserThread(int f){
	int i;
	int argument;

	//Deserialization
	ifstream in ("binary.txt",ios::binary);
	in.read((char *)&argument,sizeof(argument));
	in.close();
	

	// restore state
	currentThread->space->RestoreState();

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister (i, 0);

    // Initial program counter 
    machine->WriteRegister (PCReg, f);
    machine->WriteRegister (NextPCReg, f+4);
    
	// on modifie le Stack Pointer 
	machine->WriteRegister (StackReg, 1024 -16 - (4*PageSize));
	// on passe par le registre 4 pour empiler l'argument de f
	machine->WriteRegister (4,argument);
	
	machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
	Thread *t;
	
	nbThread ++;
	// create thread	
	t = new Thread("thread user");
	
	//ofstream out("binary.txt",ios::binary);
	//out.write((char *)&arg,sizeof(arg));
	//out.close();

	// initialize
	t->Fork(StartUserThread,f);
	return 0;
}

void do_UserThreadExit() {
	nbThread--;
	currentThread->Finish();
}

void initUserThread() {
	nbThread = 0;
}

void do_WaitUserThread() {
	while(nbThread>0){
		currentThread->Yield();
	}
}

#endif //CHANGED
