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
int main(int argc, char *argv[])          /* a számot a parancssorban adjuk meg */
{
  if (argc != 2)                          /* nincs megadva argumentum, hiba */
  {
    printf("hasznalat:%s <parancs> (exit kilepeshez)\n",argv[0]);
    exit(1);
  }

   int fd, fd1;                            /* kliens- és szerverfifo */
   char s[15];
   char buffer[1024];
   azon t;


  sprintf(s, "fifo_%d", getpid());        /* meghat. a fifonevet a pid segítségével */
  if (mkfifo(s, S_IFIFO|0666) < 0) {perror("HIBA: mkfifo kliens"); exit(1);}               /* létrehoz egy kliensfifot */
  if( (fd = open("szerverfifo", O_WRONLY)) <0) {perror("HIBA: open kliens"); exit(1);}
  
  t.pid = getpid();  /* a küldendő adatok */
 // printf("fifo_%d\n",t.pid);
  strcpy(t.parancs,argv[1]);
  if(write(fd, &t, sizeof(t)) <0) {perror("HIBA: iras a szervernek"); exit(1);}               /* küldi a szervernek */
  
  if(strcmp(t.parancs,"exit") != 0 ) 
  {

	if( (fd1 = open(s, O_RDONLY)) <0 )
  	{
  	perror("HIBA: kliens fifo megnyitasa");
  	exit(1);
  	}

  	while(1)
  	{
	if( read(fd1, &buffer, sizeof(buffer)) > 0)
	 {
      		printf("%s",buffer);
	 }
        else break;
  	}		/* a válasz */
 

  	if( close(fd1) < 0)
	{
		perror("HIBA: kliens bezarasa");
		exit(1);
	}

  } 

  	if( close(fd) < 0)
	{
		perror("HIBA: szerver bezarasa");
		exit(1);
	}
	
	  if(unlink(s) < 0)
        {
                perror("HIBA: kliens torlese");
                exit(1);
        }

	
	exit(0);
}
