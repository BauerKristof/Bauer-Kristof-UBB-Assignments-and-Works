/*
#Nev:Bauer Kristof
# Azonosito:bkim1790
#Csoport:511
#Feladatcsoport:L10
#Feladat szama:01
#Szoveg:A kliens egy (hh:mm formátumú) időpontot küld a szervernek, amelyet az input.dat állományból olvas. A szerver visszaküldi az összes olyan felhasználó (felhasználó)nevét, akik éppen dolgoznak, és a mai napon a megadott időpont után jelenkeztek be. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

struct adat
{
	int hh;
	int mm;
};

int main()
{
  int pipe1[2], pipe2[2];                     /* két pipe a kétirányú kommunikációhoz */
  int pid;
  int r = 0;
  char felhasznalo[10];
  pipe(pipe1); // client --> server           /* pipe-ok létrehozása */
  pipe(pipe2); // server --> client

  switch (pid = fork())                       /* gyerekfolyamat létrehozása */
  {
    case -1 : 
    {	    /* hiba a létrehozáskor */
      perror("fork hiba");
      exit(0);
    }
    case 0 :                                  /* gyerek - szerver */
    {
      FILE *ps;                               /* a popen ebből fog olvasni */
      char shellcmd[200];                     /* kiadandó shell parancs */
      struct adat idok;

      close(pipe1[1]);                        /* pipe1 --> - olvasás a pipe1-ből */
      close(pipe2[0]);                        /* --> pipe2 - írás a pipe2-be */

        r = read(pipe1[0], &idok, sizeof(idok));     /* olvassa*/
	if (r < 0){
		perror("HIba");
	}
	char buffer[15];
	sprintf(shellcmd,"./L10_01_bkim1790.sh");
	int osszeg=(idok.hh*60)+idok.mm;
        ps = popen(shellcmd, "r");                      /* eredmény kiolvasása a popen-ből - end of line-ig olvasom, es ellenorzom ha az ido.hh ido.mm > amit kaptam ->kiir */
	
	while(fgets(buffer,sizeof(buffer),ps) !=NULL )
	{
	char delim[]="#";
        char *ptr=strtok(buffer,delim);
 	int szamlalo=0;

		while(ptr!=NULL)
 		{
		szamlalo++;
			if(szamlalo==1)
			{
			sprintf(felhasznalo,"%s",ptr);
			}
			else if(szamlalo!=0)
			{
				int valami=atoi(ptr);
				if(valami>osszeg)
				{ 
				write(pipe2[1], &felhasznalo, sizeof(felhasznalo));    /* eredmény küldése a kliensnek */
				}
			}
		ptr=strtok(NULL,delim);
		}
	}   
    

      pclose(ps);                             /* shell parancs vége */

      exit(0);                                /* folyamat vége */

    }
    default :                                 /* szülő - kliens */
    {
      close(pipe1[0]);                        /* --> pipe1 - írás a pipe1-be */
      close(pipe2[1]);                        /* pipe2 --> - olvasás a pipe2-ből */
	
      FILE *fp;
	
     fp = fopen("input.dat", "r");

      if (fp == NULL)
      {
      perror("HIBA:Nem lehet megnyitni a filet!\n");
      exit(0);
      }

   struct adat ido;
   fscanf(fp,"%d:%d",&ido.hh,&ido.mm);
      write(pipe1[1],&ido, sizeof(ido));
      wait(NULL);  
	
    while(read(pipe2[0],&felhasznalo,sizeof(felhasznalo)))
	{
	printf("%s\n",felhasznalo);
	}

      fclose(fp);
      exit(0);                                /* kliens vége */
    }
  }
}


