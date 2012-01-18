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
static int * Threads;
static Condition *join;
static Lock *mutex;
static int ret;
static int Ids;

static void StartUserThread(Argument * f){
	int i;
	//int argument = 0;

    for (i = 0; i < NumTotalRegs; i++)
		machine->WriteRegister (i, 0);
		
	
	machine->WriteRegister(31,ret);

    // Initial program counter 
    machine->WriteRegister (PCReg, f->getFunction());
    machine->WriteRegister (NextPCReg, f->getFunction()+4);

    int bitmap=currentThread->getBitMap();
    int numPages=currentThread->space->getNumPages();

	// on modifie le Stack Pointer 
	machine->WriteRegister (StackReg,(numPages*PageSize)-(PageSize*3)-16-(PageSize*3*bitmap));
	// on passe par le registre 4 pour empiler l'argument de f
	machine->WriteRegister (4,f->getArgs());
	
	machine->Run();
	
}

static void StartUserProcess(Argument * f){
	char buf[MAX_STRING_SIZE];
	synchconsole->copyStringFromMachine(f->getArgs(),buf,MAX_STRING_SIZE);
	OpenFile *executable = fileSystem->Open (buf);
    AddrSpace *space;

    if (executable == NULL)
      {
	  printf ("Unable to open file %s\n",buf);
	  return;
      }
    space = new AddrSpace (executable);
    currentThread->space = space;
    delete executable;		// close file
    space->InitRegisters ();	// set the initial register values
    space->RestoreState ();	// load page table register
    machine->Run ();		// jump to the user progam
	
}

int do_UserThreadCreate(int f, int arg) {
	ret = machine->ReadRegister(6);
	Thread *t;
	int indexmap;	
	// create thread
	indexmap=map->Find();
	if(indexmap!=-1){
		mutex->Acquire();
	    Threads[indexmap]=++Ids;
		//structure special argument
		Argument * argu=new Argument(f,arg);
		t = new Thread("thread user",indexmap);
		t->setID(Ids);
		mutex->Release();
		t->Fork(StartUserThread,argu);
		return Ids;
	}else{
		DEBUG('t',"Not enought Space for new thread\n");
		return -1;
	}
}

void do_UserThreadExit() {
	mutex->Acquire();
	Threads[currentThread->getBitMap()]=-1;
	map->Clear(currentThread->getBitMap());
	join->Broadcast(mutex);
	mutex->Release();
	currentThread->Finish();	
}

void initUserThread() {
	int nbits=UserStackSize-16-(PageSize*3);
	nbits=nbits/(PageSize*3);
	map = new BitMap(nbits);
	mutex = new Lock("verrou");
	join = new Condition("condition");
	Threads= new int[nbits];
	for(Ids=0;Ids<nbits;Ids++){
		Threads[Ids]=-1;
	}
	Ids=0;
}

int CheckThreads(int id){
	int i,j=-1;
	for(i=0;i<map->getNumBits();i++){
		if (Threads[i]==id){
			j=i;
			break;
		}
	}
	
	return j;
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
	int i=CheckThreads(n);
	if(i!=-1){
		while(map->Test(i)){
			join->Wait(mutex);
		}
	}
	mutex->Release();
}

void do_ForkExec(int n){

	Thread *t;
	t=new Thread("mainFork",-1);
	Argument * arg =new Argument(0,n);
	t->Fork(StartUserProcess,arg);
}



#endif //CHANGED
