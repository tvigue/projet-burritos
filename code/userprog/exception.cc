// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "synch.h"
#include "synchconsole.h"
#include "userthread.h"
#include "usersem.h"

#ifdef CHANGED
static Lock * mutex;
#endif
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC () {
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which) {
	int type = machine->ReadRegister(2);
    #ifndef CHANGED
    
    
    if ((which == SyscallException) && (type == SC_Halt)) {
	  	DEBUG ('a', "Shutdown, initiated by user program.\n");
	  	interrupt->Halt ();
    } else {
	   printf ("Unexpected user mode exception %d %d\n", which, type);
	   ASSERT (FALSE);
    }
      
    #else
    int adr = 0;
    int adr2 = 0;
    char buf[MAX_STRING_SIZE];
    char ch;
    int n = 0;
    int entier;
    mutex= new Lock("SC");
    
    if(which == SyscallException){
    	switch(type){
			case SC_Halt:{
				mutex->Acquire();
				DEBUG ('a', "Shutdown, initiated by user program.\n");
		  		interrupt->Halt();
		  		mutex->Release();
		 		break;
		  	}
		  		
		  	case SC_PutChar:{
		  		mutex->Acquire();
		  		synchconsole->SynchPutChar(machine->ReadRegister(4));
		  		mutex->Release();
		  		break;
	 		}
	 		
	 		case SC_PutString:{
	 			mutex->Acquire();
	 			adr = machine->ReadRegister (4);
		  		synchconsole->copyStringFromMachine(adr,buf,MAX_STRING_SIZE);
		  		synchconsole->SynchPutString(buf);
		  		mutex->Release();
		  		break;
	 		}
	 		
	 		case SC_PutInt:{
	 			mutex->Acquire();
	 			entier = machine->ReadRegister (4);
				synchconsole->SynchPutInt(entier);
				mutex->Release();
		  		break;
	 		}
	 		
	 		case SC_GetChar:{
	 			mutex->Acquire();
				ch = synchconsole->SynchGetChar();
				machine->WriteRegister(2,(int)ch);
				break;
	 		}
	 		
	 		case SC_GetString:{
	 			mutex->Acquire();
				adr = machine->ReadRegister (4);
				n = machine->ReadRegister (5);
				synchconsole->SynchGetString(buf,n);
				synchconsole->copyStringToMachine(adr,buf,n);
				mutex->Release();
				break;
	 		}
	 		
	 		case SC_GetInt:{
	 			mutex->Acquire();
				adr = machine->ReadRegister(4);
				synchconsole->SynchGetInt(&entier);
				machine->WriteMem(adr,1,entier);
				mutex->Release();
				break;
	 		}
			
			case SC_UserThreadCreate: {
				mutex->Acquire();
				adr = machine->ReadRegister(4);
				adr2 = machine->ReadRegister(5);
				entier = machine->ReadRegister(6);
				n = do_UserThreadCreate(adr,adr2);
				machine->WriteRegister(2,(int) n);
				mutex->Release();
				break;
			}
			
			case SC_UserThreadExit: {
				mutex->Acquire();
				do_UserThreadExit();
				mutex->Release();
				break;
			}
			
			case SC_UserThreadWait: {
				mutex->Acquire();
				do_UserThreadWait();
				mutex->Release();
				break;
			}

			case SC_UserThreadJoin: {
				mutex->Acquire();		
					n=machine->ReadRegister(4);		
					do_UserThreadJoin(n);
					mutex->Release();		
					break;		
			}
			
			case SC_UserSemCreate: {
				mutex->Acquire();
				entier = machine->ReadRegister(4);
				n = do_UserSemCreate(entier);
				machine->WriteRegister(2,(int) n);
				mutex->Release();
				break;
			}
			
			case SC_UserSemPost: {
				mutex->Acquire();
				n = machine->ReadRegister(4);
				do_UserSemPost(n);
				mutex->Release();
				break;
			}
			
			case SC_UserSemWait: {
				mutex->Acquire();
				n = machine->ReadRegister(4);
				do_UserSemWait(n);
				mutex->Release();
				break;
			}
	 		
	 		case SC_Exit: {
	 			mutex->Acquire();
				DEBUG('a', "Shutdown, initiated by user program.\n");
				DEBUG('t', "Wait users threads.\n");
				do_UserThreadWait();
				//del semaphores user
				delUserSem();
				//Exit Processus
				do_UserProcessusExit();
				//Wait Processus
				if(currentThread->getBitMap()==-1){
					do_UserProcessusWait();
					interrupt->Halt();
				}
				mutex->Release();
				break;
			}
			
			case SC_ForkExec: {
				mutex->Acquire();
				n=machine->ReadRegister(4);
				do_ForkExec(n);
				mutex->Release();
				break;
				
			}
		
  		
		  	default :{
			  	printf ("Unexpected user mode exception %d %d\n", which, type);
			  	ASSERT (FALSE);  		
		  	}
		}
	}
	
    #endif
    // LB: Do not forget to increment the pc before returning!
    UpdatePC ();
    // End of addition
}

