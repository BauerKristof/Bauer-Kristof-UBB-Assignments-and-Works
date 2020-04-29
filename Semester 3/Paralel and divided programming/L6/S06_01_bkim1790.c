/*Nev Bauer Kristof
Csoport:521
Feladat:1
Szovege:. Írjunk programot, mely egy NxN-es mátrixot generál, majd létrehoz N szálat. Ezt követően időnként generál egy i, illetve j indexet, és véletlenszerűen módosítja a mátrix i,j elemét, majd kiírja a módisított mátrixot egy állományba (a végére). Az i. szál időnként kiszámolja külön az i. sorban, illetve i. oszlopban levő elemek összegét, és csak akkor írja azt ki, ha valami módosult az előző lépéshez képest. A mátrixot módosító folyamat 15 módosítás után leállítja a szálakat, felszabadítja az erőforrásokat és befejeződik.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>


typedef struct Parameterek{
      int N;
      int threadID;
} paramet;

paramet thPar[50];
int matrix[50][50];
void *szamit (void *thPar);

void wait(unsigned int seconds) 
{
    unsigned int limit = time(NULL) + seconds;
    while (time(NULL) < limit);
}

void *szamit (void* thPar) {
      int id = ((paramet*)thPar)->threadID;
      int n= ((paramet*)thPar)->N;
      printf ("thread %d: INDULT\n", id);
	int elozo=0;
        int sum=0;
	int i;
	while(1)
	{
		    printf("%d\n",id);
	sum = 0;
	for(i=id;i<n;i++)
	 {	sum+=matrix[i][id];	
		sum+=matrix[id][i];
	 }

	if(sum != elozo)
		printf("%d \n",sum);
	elozo=sum;
	
	wait(5);
	}      
	printf ("thread %d: MEGALLT\n", id); //leallit
 return NULL;
}

int main (int argc, char* argv[])
{
      if(argc < 2){
            printf("Hasznalat: %s <threadek szama (N)>\n", argv[0]);
            exit(1);
      }


      int i;
      int n = atoi(argv[1]);

    pthread_t th[50];
    int j;

    srand(time(NULL));
    for(i = 0; i<n; i++)
        for(j = 0; j<n; j++)
            matrix[i][j] = rand() % 100;


    //letrehozta a szalakat amelyek az szamit fuggveny fogjak meghivni thread joinkor
     

	for(i = 0; i < n; i++){
            thPar[i].threadID = i+1;
	    thPar[i].N=n;
            pthread_create ((pthread_t *) &th[i], NULL, (void *)szamit, (paramet *)&thPar[i]);
      }    
      int counter;
      int iGen,jGen;
      FILE* out;
      out = fopen("matrixModosit", "a");
	

	for(counter=1;counter<=4;counter++)
	{
	iGen=rand()%(n);
	jGen=rand()%(n);
	matrix[iGen][jGen]=rand() % 100; 
	printf("Az iGEN= %d, a jGen=%d,matrix[i][j]=%d\n",iGen,jGen,matrix[iGen][jGen]);
	   
	    for(i = 0; i<n; i++)
	    {
        	for(j = 0; j<n; j++)
		{
            	fprintf(out,"%d ",matrix[i][j]);
		}
		fprintf(out,"\n");
	   }
	 fprintf(out,"\n\n");
	 wait(2);

	//meghivja az I-edik szalat
	 //meghivThread(th[iGen]); 
      //printf("Bekerult3\n");   
	}
	
	for(i=0;i<n;i++)
	{
 	            pthread_cancel (th[i]);
		    printf("%ld\n",th[i]);
		    pthread_join (th[i], NULL);
	}
     fclose(out);
     return 0;
}

