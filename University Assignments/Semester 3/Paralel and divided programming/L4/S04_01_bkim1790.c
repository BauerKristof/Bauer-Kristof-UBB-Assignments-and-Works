/*Nev:Bauer Kristof
Azonosito:bkim1790
Csoport:521
Labor:4
Feladat:1
Szovege:Egy program létrehoz egy osztott-memória területet, egy 0 és 1 értékeket tartalmazó mátrixszal. Egy másik program n másodpercenként oszloponként végigjárja a mátrixot, és amennyiben valamelyik mátrixelem szomszédságában 5 db. 1-es érték van, akkor ez az elem értéke is 1 lesz, ha pedig 5 db. 0-s szomszédja van, 0-vá válik ő is. Az a folyamat, amelyik létrehozta az osztott-memória területet,kiírja a mátrixot mindaddig, ameddig az már nem változik többé. (A mátrixot módosító folyamat helyben dolgozzon, vagyis egy változtatás kihatással legyen a szomszédaira)*/

#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>


using namespace std;

#define SHMOBJ_PATH         "/matrix"
#define MAX_MSG_LENGTH      50
#define TYPES               8

/* üzenet struktúra */


struct msg_s {
  
  int A[50][50];
  int n;
  bool matrixchanged;
  bool modosult;
  sem_t wmut; //kiirhatja
  sem_t mmut; //modosithatja
  
};

void initSzemaforok(struct msg_s* p){
	if(sem_init(&(p->wmut),1,1) < 0){
		perror("In sem_init()");
		exit(1);
	}
  if(sem_init(&(p->mmut),1,0) < 0){
		perror("In sem_init()");
		exit(1);
	}
}

int getSharedMemoryFileDescriptor(){
  int shmfd = shm_open(SHMOBJ_PATH, O_RDWR, S_IRWXU | S_IRWXG);
	if (shmfd == -1){
		shmfd = shm_open(SHMOBJ_PATH, O_CREAT | O_EXCL | O_RDWR, S_IRWXU | S_IRWXG);
		if (shmfd < 0) {
			perror("In shm_open()");
    		exit(1);
		}
    int shared_seg_size = (sizeof(struct msg_s));
    ftruncate(shmfd, shared_seg_size);
  }
  return shmfd;
}

void kiir(int A[50][50], int n)
{
	for(int i=1;i<n+1;i++)
	{
		for(int j=1;j<n+1;j++)
		{
		cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}


int main(int argc, char *argv[])
{
	srand(time(0));
	int shmfd;
	int shared_seg_size = (sizeof(struct msg_s));   /* megosztott szegmens mérete (jelen esetben egyetlen struktúrát fogunk megosztani)*/
	struct msg_s *shared_msg;

	
	shmfd=getSharedMemoryFileDescriptor();

	shared_msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
 
     	if (shared_msg == NULL) {
    	perror("In mmap()");
         exit(1);
	}

	printf("Shared memory segment allocated correctly (%d bytes).\n", shared_seg_size);
	//----------OSZTOTT MEMORIA SIKERES ALLOKACIOJA-------------------------------

	srandom(time(NULL));
	shared_msg->n=6;	


	 for(int i = 0; i < shared_msg -> n + 2; i++)
   	 {
     	  for(int j = 0; j < shared_msg -> n + 2; j++)
    	  {
        	if(i == 0 || i == shared_msg -> n + 1 || j == 0 || j == shared_msg -> n + 1)
        	{
         	 shared_msg -> A[i][j] = 5;
        	}	
        	else
      		  {
         	 shared_msg -> A[i][j] = rand() % 2;
       		  }
      	   }
	}

	
	shared_msg->matrixchanged=true;
	shared_msg->modosult=true;
	initSzemaforok(shared_msg);


	printf("Kezdodik a process...\n");
	//-------------------INICIALIZALAS-----------------------------------

	while (shared_msg->modosult == true) 
	{
		if(shared_msg->matrixchanged == true)
		{
		cout<<"SZERVER"<<endl;
	         int value;
   		sem_getvalue(&(shared_msg->wmut), &value);
   		cout<<"Szerver: A wmut szemafor erteke modositas elott: "<< value<<endl;
		sem_getvalue(&(shared_msg->mmut),&value);
		cout<<"Szerver: Az mmut szemafor erteke modositas elott: "<<value<<endl;


		sem_wait(&(shared_msg->wmut));
		
		kiir(shared_msg->A,shared_msg->n);
		shared_msg->matrixchanged=false;
		

		sem_post(&(shared_msg->mmut));
		
		sem_getvalue(&(shared_msg->wmut), &value);
   		cout<<"Szerver: A wmut szemafor erteke modositas utan : "<< value<<endl;
		sem_getvalue(&(shared_msg->mmut),&value);
		cout<<"Szerver: Az mmut szemafor erteke modositas utan: "<<value<<endl;
		cout<<"-------------------------------------------------------------"<<endl;
		
		
		}
		else
		{
			cout<<"KLIENS"<<endl;
			int shmfd2 = shm_open(SHMOBJ_PATH, O_RDWR, S_IRWXU | S_IRWXG);
			if (shmfd2 < 0) {
			   perror("In shm2_open()");
    				 exit(1);
			}
			printf("Kliens:Connecting to the shared memory object... %s\n", SHMOBJ_PATH);
			cout<<endl;
			struct msg_s *msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
				if (msg == NULL) {
				perror("In mmap()");
				exit(1);
				}

			
			//segedMatrixxal muvelet
			//int segedMatrix[50][50];
			int n;	
			 int value;
    			sem_getvalue(&(shared_msg->wmut), &value);
   			cout<<"Kliens: A wmut szemafor erteke modositas elott:"<< value<<endl;
			sem_getvalue(&(shared_msg->mmut),&value);
			cout<<"Kiens: Az mmut szemafor erteke modositas elott:"<<value<<endl;

                       	sem_wait(&(shared_msg->mmut));

			 /*   for(int i = 0; i < msg -> n + 2; i++)
   			    {
        			for(int j = 0; j < msg -> n + 2; j++)
        			{
        			  segedMatrix[i][j] = msg -> A[i][j];
       				 }
      			    }
			*/

	
int modosultSzamlalo=0;
for(int j = 1; j < msg -> n + 1; j++)
 {
       	for(int i = 1; i < msg -> n + 1; i++)
	{
          int dbNulla = 0;
          if(msg->A[i-1][j] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i-1][j-1] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i][j-1] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i][j+1] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i + 1][j] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i + 1][j + 1] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i + 1][j - 1] == 0)
          {
            dbNulla++;
          }
          if(msg->A[i-1][j + 1] == 0)
          {
            dbNulla++;
          }
          
	if(dbNulla >= 5 && msg->A[i][j] != 0)
          {
            msg->A[i][j] = 0;
	    cout<<"0-ra modosult ertek~ I= "<<i<<" "<<"J= "<<j<<endl;
	    modosultSzamlalo++;          
	}
        else
 {
        
		int dbEgy = 0;
          if(msg->A[i-1][j] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i-1][j-1] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i][j-1] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i][j+1] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i + 1][j] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i + 1][j + 1] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i + 1][j - 1] == 1)
          {
            dbEgy++;
          }
          if(msg->A[i-1][j + 1] == 1)
          {
            dbEgy++;
          }
          if(dbEgy >= 5 && msg->A[i][j] != 1)
          {
            msg->A[i][j] = 1;
	    cout<<"1-re modosult ertek~I= "<<i<<" "<<"J= "<<j<<endl;
	    modosultSzamlalo++;
          }
	}
     }

  }

			//msg->A = segedMatrix;
			cout<<endl;

		     /* for(int i = 1; i < msg -> n + 1; i++)
      			{
       			 for(int j = 1; j < msg -> n + 1; j++)
        			{
          			msg -> A[i][j] = segedMatrix[i][j];
       				 }
     			 }
		   */

			msg->matrixchanged=true;
			if(modosultSzamlalo==0)
			{
			msg->modosult=false;
			}
			  
                    	  sem_post(&(shared_msg->wmut));
			  
			  sem_getvalue(&(shared_msg->wmut), &value);
   			  cout<<"Kliens: A wmut szemafor erteke modositas utan:"<< value<<endl;
			  sem_getvalue(&(shared_msg->mmut),&value);
			  cout<<"Kliens: Az mmut szemafor erteke modositas utan:"<<value<<endl;
			
			  close(shmfd2);
			  
			  sleep(2);
			  cout<<"--------------------------------------------------"<<endl;
 			}
	}


	if (munmap(shared_msg,shared_seg_size)==-1){
		perror("munmap:");
		exit(1);
	}

	printf("Memory freed successfully.\n -szerver ");

	if (shm_unlink(SHMOBJ_PATH) != 0) {
  	perror("In shm_unlink()");
  	exit(1);
	}

	return 0;
}
