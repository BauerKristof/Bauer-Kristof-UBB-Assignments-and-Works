/* Bauer Kristof
# bkim1790
# L12_01
# csoport:511
# Írjunk egy fogyasztó és egy ellátó (termelő) programot, a fogyasztó egy lerakatban szereplő árukat fogyasztja a termelő pedig a lerakatot új áruval látja el. A lerakat egy olyan állomány, amely (char aru[20], int mennyiség]) formátumú bejegyzéseket tartalmaz. Egyszerre több fogyasztó-, illetve termelő folyamat fog dolgozni a lerakattal. Szimuláljuk a lerakatban végzett munkát, ügyelve arra, hogy szinkronizálva legyen a lerakatba való belépés, úgy, hogy lezárjuk (lock) a lerakat állomány megfelelő részeit.
*/

#include "L12_01_bkim1790.h"


int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Hasznalat:%s <aruneve> <mennyiseg>\n",argv[0]);
		return 1;
	}

	char neve[20];
	int arumennyiseg=0;
	strcpy(neve,argv[1]);
	arumennyiseg=atoi(argv[2]);
	struct flock flockstruct;
        memset(&flockstruct,0,sizeof(struct flock));
	int n=0;

	int file=open(INPUT_FILE, O_RDWR);
	if (file < 0)
	{
		perror("HIBA:Nem tudtam megnyitni a filet\n");
		printf("%d fogyaszto: nem tudta megynitni a filet\n",getpid());
		exit(1);
	}

	//kiolvas n
	flockstruct.l_type = F_WRLCK;
	flockstruct.l_whence = SEEK_SET;
	flockstruct.l_start = 0;
	flockstruct.l_len = sizeof(int);

	if (fcntl(file, F_SETLKW, &flockstruct) < 0)
	{
		printf("%d fogyaszto: hiba a lockban\n", getpid());
		exit(1);
	}

	if (read(file, &n, sizeof(int)) < 0)
	{
		printf("%d fogyaszto: hiba az olvasasban\n", getpid());
		exit(1);
	}

	flockstruct.l_type = F_UNLCK;
	if (fcntl(file, F_SETLKW, &flockstruct) < 0)
	{
		printf("%d fogyaszto: hiba az unlockban\n", getpid());
		exit(1);
	}	

	int i=0;
	aruk a;

	for(i=0;i<n;i++)
	{
		printf("%d fogyaszto: lockolni keszul\n",getpid());
		flockstruct.l_type = F_WRLCK;
     		int h = fcntl(file, F_SETLKW, &flockstruct);
     		
		if(h < 0)
      		{
       		 printf("%d fogyaszto:hiba a lockban\n", getpid());
       		 exit(1);
		}
		
		printf("%d fogyaszto: sikeres lockolas\n",getpid());

		

		if(read(file,&a,sizeof(aruk)) <0)
		{
		printf("%d fogyaszto: hiba az olvasasban\n", getpid());
                exit(1);
		}

		if(strcmp(a.aru,neve)==0)
		{
			break;
		}
		else
		{
		 flockstruct.l_type = F_UNLCK;
                 int h = fcntl(file, F_SETLKW, &flockstruct);
        	if (h < 0) {
          	printf("%d fogyaszto:unlock hiba\n", getpid());
          	exit(1);
       		 }
		printf("%d fogyaszto:sikeres unlock\n",getpid());
		}
	 flockstruct.l_start = sizeof(int) + sizeof(aruk) * (i + 1);
	}
	

	if(i<n)
	{
	lseek(file,-sizeof(aruk),SEEK_CUR);
        flockstruct.l_whence=SEEK_CUR;
        flockstruct.l_start=0;
	flockstruct.l_type=F_WRLCK;
        flockstruct.l_len=sizeof(aruk);
	//lelockolva van meg az elem -> nincs szukseg lockra
	
	lseek(file,sizeof(a.aru),SEEK_CUR);
	int szam;
	read(file,&szam,sizeof(int));
	lseek(file,-sizeof(int),SEEK_CUR);
	szam-=arumennyiseg;
	if(szam <= 0)
	{
	printf("A %s aru elfogyott\n",a.aru);
	szam=0;
	}
	printf("%s | %d\n",a.aru,szam);
	write(file,&szam,sizeof(int));
	
	flockstruct.l_type = F_UNLCK;
      	int h= fcntl(file, F_SETLKW, &flockstruct);
      	if (h < 0) 
	{
	printf("%d fogyaszto: unlock hiba\n",getpid());
        exit(1);
      	}
	printf("%d fogyaszto: sikeres unlock\n",getpid());
	}
	
	
	else
	{
	printf("%d fogyaszto: hiba nincs ilyen elem\n",getpid());
	exit(1);
	}
}
