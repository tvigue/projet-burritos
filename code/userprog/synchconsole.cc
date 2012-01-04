#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { 
	readAvail->V(); 
}

static void WriteDone(int arg) { 
	writeDone->V(); 
}

SynchConsole::SynchConsole(char *readFile, char *writeFile) {
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console(readFile,writeFile,ReadAvail,WriteDone,0);
}

SynchConsole::~SynchConsole() {
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch) {
	console->PutChar(ch);
	writeDone->P();
}

char SynchConsole::SynchGetChar() {
	readAvail->P();
	return console->GetChar();
}

void SynchConsole::SynchPutString(const char s[]) {
	int i = 0;
	int taille = strlen(s);
	
	while(i<taille && s[i] != '\0'){
		SynchPutChar(s[i]);
		i++;
	}
}

void SynchConsole::SynchGetString(char *s, int n) {

}

void SynchConsole::copyStringFromMachine(int from, char *to, unsigned size){
	int value;
	unsigned i = 0;
	
	while(i<size-1){
		if(machine->ReadMem(from,1,&value)){
			if(value == '\0'){
				break;
			} else {
				to[i] = (char) value;
				from ++;
			}
			i++;
		}
	}
	to[i] = '\0';
}

#endif // CHANGED

