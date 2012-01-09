#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"

static void StartUserThread(int f){
	int arg = machine->ReadRegister(5);
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
	machine->WriteRegister (4,arg);
	
	machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
	Thread *t;
	
	// create thread	
	t = new Thread("thread user");
	
	// initialize
	t->Fork(StartUserThread,f);
	
	return 0;
}

#endif //CHANGED
