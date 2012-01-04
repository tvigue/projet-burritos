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
	int i = 0;
	char c;
	
	c = SynchGetChar();
	while(i < MAX_STRING_SIZE-1 && c != EOF && c !='\n'){
		s[i] = c;
		i++;
		c= SynchGetChar();
	}	
	s[i] = '\0';
}

void SynchConsole::SynchPutInt(int n){
	char* buf =  new char[MAX_STRING_SIZE];
	snprintf(buf,MAX_STRING_SIZE,"%i",n);
	SynchPutString(buf);
}

void SynchConsole::SynchGetInt(int *n){
	char *buf = new char[MAX_STRING_SIZE];
	SynchGetString(buf,strlen(buf));
	sscanf(buf,"%i",n);
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

void SynchConsole::copyStringToMachine(int adr, char *in, unsigned size){
	int value;
	unsigned int i;
	for(i =0;i<size-1 && in[i] != '\0';i++){
		value = (int) in[i];
		machine->WriteMem(adr+i,1,value);
	}
	machine->WriteMem(adr+i,1,'\0');
}

#endif // CHANGED

