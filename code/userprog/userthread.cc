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
	t->setStatus(READY);
	
	t->Fork(f,arg);
	
	return 0;
}

#endif //CHANGED
