#include "syscall.h"

int
main ()
{
    //SpaceId newProc;
    char prompt[2], buffer[60];
    int i;

    prompt[0] = '-';
    prompt[1] = '-';

	while (1) {
	  	PutChar (prompt[0]);
	  	PutChar (prompt[1]);
	  	i = 0;
		buffer[i]=GetChar();
	  	while (buffer[i] != '\n') {
	  		i++;
	  	 	buffer[i]=GetChar();		
	  	}

	  	buffer[i] = '\0';

	  	if (i > 0) {
			if(buffer[0] == 'c'){
				PutString("caca\n");
			} else {
				if(buffer[0] == 'q'){
					Exit(0);
				} else {
					if(buffer[0] == 'l'){
						PutString(" (\\/) \n");
						PutString(" (. .) \n");
						PutString("c(\")(\") \n");
					} else {
	  					ForkExec(buffer);
	  				}
	  			}
	  		}
			//Join (newProc);
	    }
	}
}
