#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"
#include "bitmap.h"
#include "argument.h"
#include "synch.h"

static BitMap * map;
static Condition *join;
static Lock *mutex;
static int ret;

static void StartUserThread(Argument * f){
	int i;
	//int argument = 0;

    for (i = 0; i < NumTotalRegs; i++)
		machine->WriteRegister (i, 0);
		
	
	machine->WriteRegister(31,ret);

    // Initial program counter 
    machine->WriteRegister (PCReg, f->getFunction());
    machine->WriteRegister (NextPCReg, f->getFunction()+4);

    int threadid=currentThread->getid();
    int numPages=currentThread->space->getNumPages();

	// on modifie le Stack Pointer 
	machine->WriteRegister (StackReg,(numPages*PageSize)-(PageSize*3)-16-(PageSize*3*threadid));
	// on passe par le registre 4 pour empiler l'argument de f
	machine->WriteRegister (4,f->getArgs());
	
	machine->Run();
	
}

int do_UserThreadCreate(int f, int arg) {
	ret = machine->ReadRegister(6);
	Thread *t;
	int indexmap;	
	// create thread
	indexmap=map->Find();
	if(indexmap!=-1){
		//structure special argument
		Argument * argu=new Argument(f,arg);
		t = new Thread("thread user",indexmap);
		t->Fork(StartUserThread,argu);
		return indexmap;
	}else{
		printf("Not enought Space for new thread\n");
		return -1;
	}
}

void do_UserThreadExit() {	
	mutex->Acquire();
	map->Clear(currentThread->getid());
	join->Broadcast(mutex);
	mutex->Release();
	currentThread->Finish();	
}

void initUserThread() {
	int nbits=UserStackSize-16-(PageSize*3);
	map = new BitMap(nbits/(PageSize*3));
	mutex = new Lock("verrou");
	join = new Condition("condition");
}

void do_UserThreadWait() {
	mutex->Acquire();
	while(!map->CheckClear()){
		join->Wait(mutex);
	}
	mutex->Release();
}

void do_UserThreadJoin(int n) {
	mutex->Acquire();
	while(map->Test(n)){
		join->Wait(mutex);
	}
	mutex->Release();
}

#endif //CHANGED
