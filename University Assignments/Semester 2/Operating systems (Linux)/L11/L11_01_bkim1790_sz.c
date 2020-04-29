/*Nev:Bauer Kristof
Azonosito:bkim1790
Csoport:511
Feladat:L11
Feladatszam:1
Feladat szovege:A kliens shell parancsok végrehajtását kéri a szervertől. A szerver nyilvántart egy "engedélyezett utasításokat" tartalmazó listát*/


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "struktura.h"                    /* a fenti fejlécállomány */
#include <string.h>


int main(void)
{
  int fd,fd1;                            /* szerver- és kliensfifo */
  char s[15];                             /* kliensfifo neve; pl. fifo_143 */
  azon t;    /* küldendő "csomag" */
  FILE *ps;                               /* a popen ebből fog olvasni */
  char shellcmd[64];                     /* kiadandó shell parancs */
  char buffer[1024];
  char idbuff[64];

  if (mkfifo("szerverfifo",S_IFIFO|0666)<0) {perror("HIBA mkfifo!"); exit(1);}    /* a szerver létrehozza a saját fifo-ját */
  if ((fd=open("szerverfifo",O_RDONLY))<0){perror("Open HIBA!");exit(1);}     /* megnyitja olvasásra; jöhetnek a számok */

  while(1)                                      /* addig megy, míg 0-t nem küld egy kliens */
  {
   if(read(fd, &t, sizeof(t))>0)
     {	   /* szám kiolvasása */
      printf("pid:%d parancs: %s\n",t.pid,t.parancs);	      
      if (strcmp(t.parancs,"exit")==0){break;}
     
      sprintf(shellcmd,"./L11_01_bkim1790.sh ");
      strcat(t.parancs," 2>&1");
      strcat(shellcmd, t.parancs);
      ps = popen(shellcmd, "r");
      sprintf(s, "fifo_%d", t.pid);         /* a pid segítségével meghat. a kliensfifo nevét */
    
      if ((fd1=open(s,O_WRONLY))<0) {perror("Open HIBA irasra!");exit(1);}

      sprintf(idbuff,"(pid:%d): ",t.pid);
      while (fgets(buffer,sizeof(buffer),ps))
	{
	strcat(buffer,idbuff);
	if (write(fd1,&buffer,sizeof(buffer))<0){perror("Kuldes hiba!");exit(1);}		
	}
      if (close(fd1)<0){perror("Bezaras HIBA!");exit(1);}
        pclose(ps);	 
     }
   }
 
  if (close(fd)<0) {perror("Bezaras HIBA szerver_fifo");exit(1);}
  printf("Befejezodott a szerver\n");
  if (unlink("szerverfifo")<0){perror("SZERVER bezaras HIBA!");exit(1);}
  exit(0);
}



