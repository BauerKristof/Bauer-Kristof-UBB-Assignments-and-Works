/* Bauer Kristof
# bkim1790
# L12_01
# csoport:511
# Írjunk egy fogyasztó és egy ellátó (termelő) programot, a fogyasztó egy lerakatban szereplő árukat fogyasztja a termelő pedig a lerakatot új áruval látja el. A lerakat egy olyan állomány, amely (char aru[20], int mennyiség]) formátumú bejegyzéseket tartalmaz. Egyszerre több fogyasztó-, illetve termelő folyamat fog dolgozni a lerakattal. Szimuláljuk a lerakatban végzett munkát, ügyelve arra, hogy szinkronizálva legyen a lerakatba való belépés, úgy, hogy lezárjuk (lock) a lerakat állomány megfelelő részeit.
*/


#include "L12_01_bkim1790.h"

int main(int argc, char ** argv){
  int fd,mennyisege,i;
  char nev[20];
  aruk a[30];
  FILE *input;


  input = fopen("lerakat.dat","r");
  mennyisege=0;
  i=0;

  while(!feof(input))
	{
	 fscanf(input,"%s %d",nev,&mennyisege);
	 strcpy(a[i].aru,nev);
	 a[i].mennyiseg=mennyisege;
	 printf("Aru: %s | Mennyiseg = %d\n",a[i].aru, a[i].mennyiseg);
	 i++;
	}

  fclose(input);


	if ((fd = open(INPUT_FILE, O_WRONLY | O_CREAT,0666)) < 0){
		printf("HIBA: Binaris file megnyitasa\n");
		exit(1);
	}
	
	write(fd, &i, sizeof(int));	
	
	int j;
	for(j = 0; j < i; j++)
	{
		write(fd, &a[j], sizeof(aruk));	
	}
	close(fd);
	printf("Binaris allomany letrehozva\n");
}

