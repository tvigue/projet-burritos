#ifdef CHANGED

#include "copyright.h"
#include "thread.h"
#include "machine.h"
#include "userthread.h"
#include "addrspace.h"
#include "system.h"
#include "synch.h"

static int * Semaphores;
static int id;

int do_UserSemCreate(int n){
	Semaphore * s = new Semaphore("SemUser",n);
	Semaphores[id] = (int)s; 
	int ret = id;
	id++;
	return ret;
}

void do_UserSemPost(int semid){
	((Semaphore*)Semaphores[semid])->V();
}

void do_UserSemWait(int semid){
	((Semaphore*)Semaphores[semid])->P();
}

void initUserSem() {
	id = 0;
	Semaphores = new int[10];
}

void delUserSem(){
	int i;
	for(i=0;i<10;i++)
		delete (Semaphore*)Semaphores[i];	
}

#endif
