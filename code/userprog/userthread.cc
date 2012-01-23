#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"
#include "argument.h"
#define MAX_PROCESSUS 20


static int ret;
static int ThID=0;
static BitMap * map;
static int * Processus;
static int PrID=0;
static Condition * join;
static Lock * mutex;

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
	char * buf = new char[MAX_STRING_SIZE];
	mutex->Acquire();
	synchconsole->copyStringFromMachine(f->getArgs(),buf,MAX_STRING_SIZE);
	OpenFile *executable = fileSystem->Open (buf);
    AddrSpace *space;

    if (executable == NULL)
      {
	  printf ("Unable to open file %s\n",buf);
	  return;
      }
    space = new AddrSpace (executable);
    mutex->Release();
    if(space->getBitmap()!=NULL){//if not enough space the bitmap is not allocated
		currentThread->space = space;
		delete executable;		// close file
		space->InitRegisters ();	// set the initial register values
		space->RestoreState ();	// load page table register
		machine->Run ();		// jump to the user progam
	}
	else{//and so we have to clear the bitmap of the process
	do_UserProcessusExit();
	do_UserProcessusWait();
	}
		
}

int do_UserThreadCreate(int f, int arg) {
	ret = machine->ReadRegister(6);
	Thread *t;
	int indexmap;	
	// create thread
	indexmap=currentThread->space->getBitmap()->Find();
	if(indexmap!=-1){
		currentThread->space->getMutex()->Acquire();
	    currentThread->space->getThreads()[indexmap]=++ThID;
		//structure special argument
		Argument * argu=new Argument(f,arg);
		t = new Thread("thread user",indexmap);
		t->setID(ThID);
		currentThread->space->getMutex()->Release();
		t->Fork(StartUserThread,argu);
		return ThID;
	}else{
		DEBUG('t',"Not enought Space for new thread\n");
		return -1;
	}
}

void do_UserThreadExit() {
	currentThread->space->getMutex()->Acquire();
	currentThread->space->getThreads()[currentThread->getBitMap()]=-1;
	currentThread->space->getBitmap()->Clear(currentThread->getBitMap());
	currentThread->space->getCond()->Broadcast(currentThread->space->getMutex());
	currentThread->space->getMutex()->Release();
	currentThread->Finish();	
}

void do_UserProcessusExit(){
	mutex->Acquire();
	if(currentThread->getBitMap()!=-1){
		Processus[currentThread->getBitMap()]=-1;
		map->Clear(currentThread->getBitMap());
		//Clear physical memory pages through Addrspace Table Page
		//currentThread->space->ClearPhysicalMemory();
		join->Broadcast(mutex);
	}
	mutex->Release();
}

void do_UserProcessusWait(){
	mutex->Acquire();
	while(!map->CheckClear()){
		join->Wait(mutex);
	}
	mutex->Release();
}


int CheckThreads(int id){
	int i,j=-1;
	for(i=0;i<currentThread->space->getBitmap()->getNumBits();i++){
		if (currentThread->space->getThreads()[i]==id){
			j=i;
			break;
		}
	}
	
	return j;
}

void do_UserThreadWait() {
	currentThread->space->getMutex()->Acquire();
	while(!currentThread->space->getBitmap()->CheckClear()){
		currentThread->space->getCond()->Wait(currentThread->space->getMutex());
	}
	currentThread->space->getMutex()->Release();

}

void do_UserThreadJoin(int n) {
	currentThread->space->getMutex()->Acquire();
	int i=CheckThreads(n);
	if(i!=-1){
		while(currentThread->space->getBitmap()->Test(i)){
			currentThread->space->getCond()->Wait(currentThread->space->getMutex());
		}
	}
	currentThread->space->getMutex()->Release();
}

void do_ForkExec(int n){
    int indexproc=map->Find();
    if(indexproc!=-1){
		Processus[indexproc]=++PrID;
		Thread *t;
		t=new Thread("mainFork",indexproc);
		t->setID(PrID);
		Argument * arg =new Argument(0,n);
		t->Fork(StartUserProcess,arg);
    }
    else{
    	printf("Not Enought Space Fork\n");
    }
}


void initUserProcessus(){
    map=new BitMap(MAX_PROCESSUS);
    Processus=new int[MAX_PROCESSUS];
    mutex=new Lock("verrou");
    join=new Condition("condition");
}



#endif //CHANGED
