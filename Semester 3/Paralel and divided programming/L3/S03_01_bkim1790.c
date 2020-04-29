/*Nev:Bauer Kristof
Azonostio:bkim1790
Csoport:521
Labor 3
Feladat 1
Szoveg: Egy program létrehoz egy osztott-memória területet, egy 0 és 1 értékeket tartalmazó mátrixszal. Egy másik program n másodpercenként oszloponként végigjárja a mátrixot, és amennyiben valamelyik mátrixelem szomszédságában 5 db. 1-es érték van, akkor ez az elem értéke is 1 lesz, ha pedig 5 db. 0-s szomszédja van, 0-vá válik ő is. Az a folyamat, amelyik létrehozta az osztott-memória területet, kiírja a mátrixot mindaddig, ameddig már nem változik többé. (vigyázat! A mátrixot módosító folyamat külön tartsa nyilván a mátrix korábbi értékét, és annak alapján módosítsa az osztott memóriába írt mátrixelemeket.)*/

#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>


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
};

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

	shmfd = shm_open(SHMOBJ_PATH, O_CREAT | O_EXCL | O_RDWR, S_IRWXU | S_IRWXG);  /* memória objektum létrehozása */
	if (shmfd < 0) {
		perror("In shm_open()");
		exit(1);
	}

	printf("Created shared memory object %s\n", SHMOBJ_PATH);
	ftruncate(shmfd, shared_seg_size);      /* méret beállítása, hogy férjen el az egész struktúra */
        /* struktúra megosztása */
	shared_msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
 
     	if (shared_msg == NULL) {
    	perror("In mmap()");
         exit(1);
	}

	printf("Shared memory segment allocated correctly (%d bytes).\n", shared_seg_size);

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


	while (shared_msg->modosult == true) 
	{
		if(shared_msg->matrixchanged == true)
		{
		kiir(shared_msg->A,shared_msg->n);
		shared_msg->matrixchanged=false;
		}
		else
		{
			int shmfd2 = shm_open(SHMOBJ_PATH, O_RDWR, S_IRWXU | S_IRWXG);
			if (shmfd2 < 0) {
			   perror("In shm2_open()");
    				 exit(1);
			}
			printf("Connecting to the shared memory object... %s\n", SHMOBJ_PATH);
			struct msg_s *msg = (struct msg_s *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
				if (msg == NULL) {
				perror("In mmap()");
				exit(1);
				}

			
			//segedMatrixxal muvelet
			int segedMatrix[50][50];
			int n;
			
			    for(int i = 0; i < msg -> n + 2; i++)
   			    {
        			for(int j = 0; j < msg -> n + 2; j++)
        			{
        			  segedMatrix[i][j] = msg -> A[i][j];
       				 }
      			    }

	
int modosultSzamlalo=0;
for(int j = 1; j < msg -> n + 1; j++)
 {
       	for(int i = 1; i < msg -> n + 1; i++)
	{
          int dbNulla = 0;
          if(segedMatrix[i-1][j] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i-1][j-1] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i][j-1] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i][j+1] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i + 1][j] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i + 1][j + 1] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i + 1][j - 1] == 0)
          {
            dbNulla++;
          }
          if(segedMatrix[i-1][j + 1] == 0)
          {
            dbNulla++;
          }
          
	if(dbNulla >= 5 && segedMatrix[i][j] != 0)
          {
            segedMatrix[i][j] = 0;
	    modosultSzamlalo++;          
	}
        else
 {
        
		int dbEgy = 0;
          if(segedMatrix[i-1][j] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i-1][j-1] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i][j-1] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i][j+1] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i + 1][j] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i + 1][j + 1] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i + 1][j - 1] == 1)
          {
            dbEgy++;
          }
          if(segedMatrix[i-1][j + 1] == 1)
          {
            dbEgy++;
          }
          if(dbEgy >= 5 && segedMatrix[i][j] != 1)
          {
            segedMatrix[i][j] = 1;
	    modosultSzamlalo++;
          }
	}
     }
  }

			//msg->A = segedMatrix;

		      for(int i = 1; i < msg -> n + 1; i++)
      			{
       			 for(int j = 1; j < msg -> n + 1; j++)
        			{
          			msg -> A[i][j] = segedMatrix[i][j];
       				 }
     			 }


			msg->matrixchanged=true;
			if(modosultSzamlalo==0)
			{
			msg->modosult=false;
			}
			  

			close(shmfd2);
			//sleep(2);
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
