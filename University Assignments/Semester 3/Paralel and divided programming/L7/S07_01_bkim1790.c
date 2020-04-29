/*Nev:Bauer Kristof
Azonosito:bkim1790
Labor:7
Feladat:1
Szoveg:1. Egy CFR utazási ügynökségen 5 jegypénztár van, minden egyes jegypénztárnál váltható jegy bárhová. Ahhoz, hogy két jegypénztár ne adhassa el egyszerre ugyanazt a jegyet, mindegyik kasszás nő blokálja az adatbázist, eladja a jegyet, majd ismét hozzáférhetővé teszi azt. */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexAllomas = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t allomasHivas = PTHREAD_COND_INITIALIZER;  

void* exam(void* jegyPenztarID);
void* allomas(void* jegyPenztarThread);
int n=15;


void wait(int timeInMs)
{
    struct timeval tv;
    struct timespec ts;

    gettimeofday(&tv, NULL);
    ts.tv_sec = time(NULL) + timeInMs / 1000;
    ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * (timeInMs % 1000);
    ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
    ts.tv_nsec %= (1000 * 1000 * 1000);

    int n = pthread_cond_timedwait(&allomasHivas, &mutexAllomas, &ts);
    if (n == ETIMEDOUT)
        {
	      printf("LETELT AZ IDO - INDITOM AZ ALLOMASSZALLAT\n");
	   
	}
}


void* penztar (void* jegyPenztarID)
{
     int id = *(int*)jegyPenztarID;
     printf("1B. Belepett a szalba, n=%d, id=%d\n",n,id);
     while(n>=0)
     {
      int veszjegyet=rand() %2;
      printf("1BC. Itt szenvedek help: %d\n",id);
     
    if(veszjegyet == 1)
     {
     printf("2.If belseje, n=%d, id=%d, veszjegyet=%d\n",n,id,veszjegyet);
     pthread_mutex_lock(&mutex);
     n--;
     pthread_mutex_unlock(&mutex);
     }
    
    printf("1BD. En leertem ide: %d, veszjeget=%d\n",id,veszjegyet);
    sleep(rand() % 10);
   }
    printf("ELADTAK A JEGYEKET - INDITOM AZ ALLOMASSZALLAT\n");
    pthread_cond_signal(&allomasHivas);//ha n=0 - unlockol az allomas mutexet
}

void* allomas (void* jegyPenztarThread)
{
	wait(3000);

	
      
       printf("AZ ALLOMASSZAL ELINDULT\n");
       pthread_t* jegyPenztarTh;
       jegyPenztarTh =(pthread_t*)jegyPenztarThread;
       int i;
  
      for(i = 0; i <= 5; i++)
      {
	    printf("Thread torlese= %ld\n\n",*jegyPenztarTh);
            pthread_cancel(*jegyPenztarTh);
            jegyPenztarTh=jegyPenztarTh+1;
      }

}

      

//allomas
//conditionmutex(lockolva)
//ha n>0 ->cancelel kasszathreadeket
//else


int main(int argc, char* argv[])
{
      srand(time(NULL));
      pthread_t jegyPenztarThread[15];
      pthread_t jegyPenztarID[15];
      int i;


      printf("1.Inicializal\n");
  

      for(i = 0; i < 5; i++)
      {
            jegyPenztarID[i] = i;
            pthread_create ((pthread_t *) &jegyPenztarThread[i], NULL, (void *)penztar, &jegyPenztarID[i]);
      }

    
          

      printf("2.For utani threadek\n");
      pthread_t allomasThread;
      pthread_t* jegyPenztarTh=jegyPenztarThread;
      
      pthread_create(&allomasThread, NULL, allomas, &jegyPenztarTh);       //elindit allomas thread


      
      pthread_join(allomasThread, NULL); //allomas thread torlese
      
	

      for(i = 0; i < 5; i++)
      {
            pthread_join(jegyPenztarThread[i], NULL);
      }

      printf("7.Thread torles\n");

      return 0;
}
