#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"
#include "bitmap.h"

static int nbThread;
static BitMap * map;

static void StartUserThread(int f){
	int i;
	//int argument = 0;

	// restore state

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister (i, 0);

    // Initial program counter 
    machine->WriteRegister (PCReg, f);
    machine->WriteRegister (NextPCReg, f+4);

    int threadid=currentThread->getid();

	// on modifie le Stack Pointer 
	machine->WriteRegister (StackReg,UserStackSize-(PageSize*3)-16-(PageSize*3*threadid));
	// on passe par le registre 4 pour empiler l'argument de f
	//machine->WriteRegister (4,argument);
	
	machine->Run();
	
}

int do_UserThreadCreate(int f, int arg) {
	Thread *t;
	int indexmap;	

	
	// create thread	
	indexmap=map->Find();
	if(indexmap!=-1){
		t = new Thread("thread user",indexmap);
		nbThread ++;
		t->Fork(StartUserThread,f);
		return 0;
	}else{
		printf("Not enought Space for new thread\n");
		return -1;
	}
}

void do_UserThreadExit() {
	nbThread--;
	currentThread->Finish();
	
}

void initUserThread() {
	nbThread = 0;
	int nbits=UserStackSize-16-(PageSize*3);
	map=new BitMap(nbits/(PageSize*3));
}

void do_WaitUserThread() {
	while(nbThread>0){
		currentThread->Yield();
	}
}

#endif //CHANGED
