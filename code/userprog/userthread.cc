#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"

int argument;
static int nbThread;

static void StartUserThread(int f){
	int i;
	
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
	
	// initialize
	argument = arg;
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
