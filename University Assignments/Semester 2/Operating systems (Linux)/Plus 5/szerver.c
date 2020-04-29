#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "struktura.h"                    /* a fenti fejlécállomány */
#include <string.h>
#include <time.h>

int main(void)
{
  int fd,fd1;                            /* szerver- és kliensfifo */
  char s[15];                             /* kliensfifo neve; pl. fifo_143 */
  azon t;    /* küldendő "csomag" */
 // FILE *ps;                               /* a popen ebből fog olvasni */
 // char shellcmd[20];                     /* kiadandó shell parancs */
  char buffer[1024];
  int maxjatek=5;
  int jelenlegijatek=2;
  int tippszam=0;
  int kliensdb[20];
  int kliensn=0;
  int i;
  int nyerte=0;
  if (mkfifo("szerverfifo",S_IFIFO|0666)<0) {perror("HIBA mkfifo!"); exit(1);}    /* a szerver létrehozza a saját fifo-ját */
  if ((fd=open("szerverfifo",O_RDONLY))<0){perror("Open HIBA!");exit(1);}     /* megnyitja olvasásra; jöhetnek a számok */

  srand(time(NULL));
  int r=rand() % (100-1+1);
  printf("A szam= %d",r); 
  
  while(jelenlegijatek < maxjatek)                                      /* addig megy, míg 0-t nem küld egy kliens */
  {
   if(read(fd, &t, sizeof(t))>0)
     {	   /* szám kiolvasása */
      printf("fifo_%d tipp: %s\n",t.pid,t.parancs);	
      
      i=0;
      while(i<kliensn)
      {
	if(kliensdb[i] == t.pid) {break;}
	i++;
      }      

      if(i==kliensn)
      {
	kliensdb[kliensn]=t.pid;
	kliensn++;
      }
     // if (strcmp(t.parancs,"felad")==0){break;}
      

      int kliensszam=atoi(t.parancs);
      sprintf(s,"fifo_%d",t.pid);
      if ((fd1=open(s,O_WRONLY))<0) {perror("Open HIBA irasra!");exit(1);}
 if(nyerte==1)
 {
	   strcpy(buffer,"vesztettel");
            if (write(fd1,&buffer,sizeof(buffer))<0){perror("Kuldes hiba!");exit(1);}
	    nyerte=0;
 }
 else
 {
      if(kliensszam == r)
	  {
		 strcpy(buffer,"nyertel");
        	 if (write(fd1,&buffer,sizeof(buffer))<0){perror("Kuldes hiba!");exit(1);}  
		 r=rand() % (100-1+1);
		 printf("Ennyi tipp volt %d\n",tippszam);
		 printf("Ennyi jatekos csatlakozott fel: %d\n",kliensn);
		 jelenlegijatek++; 
		 nyerte=1;
		 for(i=0;i<kliensn;i++) {kliensdb[i]=0;};
		 kliensn=0;
		 tippszam=0;
	  }
      //printf("nyerte= %d",nyerte);

      if(kliensszam < r)
          {
                 strcpy(buffer,"nagyobbat");
                 if (write(fd1,&buffer,sizeof(buffer))<0){perror("Kuldes hiba!");exit(1);}
          }
     
      if(kliensszam > r)
          {
                 strcpy(buffer,"kissebbet");
                 if (write(fd1,&buffer,sizeof(buffer))<0){perror("Kuldes hiba!");exit(1);}
          }

      tippszam++;
 }

      
     // sprintf(s, "fifo_%d", t.pid);         /* a pid segítségével meghat. a kliensfifo nevét */
    
      
      if (close(fd1)<0){perror("Bezaras HIBA!");exit(1);}
     }
   }
 
  if (close(fd)<0) {perror("Bezaras HIBA szerver_fifo");exit(1);}
  printf("Befejezodott a szerver\n");
  if (unlink("szerverfifo")<0){perror("SZERVER bezaras HIBA!");exit(1);}
  exit(0);
}



