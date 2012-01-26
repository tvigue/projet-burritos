#include "syscall.h"

// test du producteur/consommateur
// pour tester des sémaphores

int production=0;
int maxProd=15;
sem_t Producteur;
sem_t Consommateur;
sem_t MutexProd;//Semaphore utilisée comme un mutex
				//pour protéger la variable globale production

void producteur(void * a){
	int j;
	for(j=0;j<(int)a;j++){
		UserSemWait(Producteur);
		UserSemWait(MutexProd);
		production++;
		PutString("Producteur, il y a : ");
		PutInt(production);
		PutChar('\n');
		UserSemPost(MutexProd);
		UserSemPost(Consommateur);		
	}
}	

void consommateur(void * a){
	int k;
	for(k=0;k<(int)a;k++){
		UserSemWait(Consommateur);
		UserSemWait(MutexProd);
		production--;
		PutString("Consommateur, il reste : ");
		PutInt(production);
		PutChar('\n');
		UserSemPost(MutexProd);
		UserSemPost(Producteur);		
	}	
}

int main(){
	int i;
	int arg=20;// nombre de prod créée par un producteur
	Producteur = UserSemCreate(maxProd);
	Consommateur = UserSemCreate(0);
	MutexProd = UserSemCreate(1);
	UserThreadCreate(producteur,(void *)arg);
	UserThreadCreate(producteur,(void *)arg);
	for(i=0;i<100000;i++){} //atente de production :
	// cela permet de remarquer que les productions ne dépassent pas maxProd
	
	arg=10;	//nombre de prod consommée par un consommateur
	for(i=0;i<3;i++){
		UserThreadCreate(consommateur,(void *)arg);
	}
	Exit(0);
}
