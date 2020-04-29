/*Nev:Bauer Kristof
 *Azonosito:bkim1790
Csoport:511
Feladat szama:1
Feladat szovege:Legyen Pi egy olyan folyamat, amelyik ellenőrzi, hogy i osztója-e egy adott a számnak és meghatározza, hogy az hányszoros osztó.
Megj: A parent megnezi hogy osztoja-e egy adott szam i-tol a szamunkig, ha igen a children megkapja az osztot, elosztja es a Pi folyamatban visszateriti
azt hogy hanyszor szerepelt benne az adott oszto. Ezek utan a szamunkat csokkentjuk majd kiirjuk a vegeredmenyt*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

int main(int argc, const char * argv[])
{
        if(argv[1]==NULL)
        {
        printf("HIBA: Nincs argumentum megadva (legalabb egy szam kell legyen)\n");
        return 0;
        }

        if(argc>=3)
        {
        printf("HIBA:Helytelen argumentum. Maximum 1 szam lehet\n");
        return 0;
        }
	FILE *o;
        o = fopen("output.dat", "w");
	FILE *l;
	l=fopen("log.dat","w");
  int PC[2],CP[2];
  pid_t pid;

  int szam=atoi(argv[1]);
  int i;

  if (pipe(PC) < 0)
    perror("pipe hiba");
  if (pipe(CP) < 0)
    perror("pipe hiba");


pid=fork();
if(pid<0)
{perror("fork hiba");}


     if (pid == 0)
     {
        close(CP[0]);
        close(PC[1]);
        while(read(PC[0],&i, sizeof(int))>0)
        {
        int db=0;
   		if((szam % i) ==0)
                {
                        while(szam % i ==0)
                        {
                        db++;
                        szam=szam/i;
                        }
                }
		  write(CP[1],&db,sizeof(int));
	printf("GYEREK FOLYAMAT | Folyamatazonosito = %d | Kapott ertek = %d | Pipeba irt ertek = %d\n",pid,i,db);
        fprintf(l,"Gyerek folyamat | Azonosito = %d  | Kiszamolt ertek= %d \n",pid,db);
	}

     }
        else
        {
        close(PC[0]);
        close(CP[1]);
        
	i=2;
	while(szam!=1)
        {
       
       	if((szam %i) == 0)
	{
		write(PC[1],&i,sizeof(int));
		int hanyszor;
		int j;
	        read(CP[0],&hanyszor,sizeof(int));
		fprintf(o,"A %d oszto ennyiszer osztja a szamot %d\n",i,hanyszor);
		fprintf(l,"Szulo folyamat | Azonosito = %d | Kiszamolt ertek= %d \n",pid,i);
		for(j=1;j<=hanyszor;j++){szam/=i;}
	

	}
	i++;
	}
        close(PC[1]);
        fclose(o);
	fclose(l);
	}
return 0;
}

