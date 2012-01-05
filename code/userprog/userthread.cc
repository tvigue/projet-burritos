#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"

int do_UserThreadCreate(int f, int arg) {
	Thread *t;
	//int SPmain;
	
	// create thread	
	t = new Thread("thread user");
	
	// initialize
/*	SPmain = machine->ReadRegister(StackReg);
	t.stack = SPmain + STACK_PAGE_NUMBER * PageSize; 
	t.stackTop = t.stack + STACK_PAGE_NUMBER * PageSize;
	t.space = STACK_PAGE_NUMBER * PageSize;
	t.status = READY;
	
	t->Fork(f,arg);
*/
	
	return 0;
}

#endif //CHANGED
