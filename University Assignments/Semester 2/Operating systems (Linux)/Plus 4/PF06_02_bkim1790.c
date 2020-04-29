//Nev:Bauer Kristof
//Csoport:511
//Felhasznalo:bkim1790

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	
	int szerver_kliens[2], kliens_szerver[2], users[2];
	pipe(szerver_kliens);
	pipe(kliens_szerver);
	pipe(users);	

	int pid;

	switch (pid = fork())
	{
		case -1:{
			perror("HIBA:fork hiba\n");
			exit(1);
		}

		case 0:{ // szerver=gyerek
			FILE *ps;
			char shellcmd[100];
			char c;
			int i;

			close(kliens_szerver[1]);
			close(szerver_kliens[0]);
			close(users[0]);
			strcpy(shellcmd, "./popenpl.sh ");
			i = strlen(shellcmd) - 1;
			
		        do{
				read(kliens_szerver[0], &c, sizeof(char)); //kiolvassa a megadott idopontot
				if (i < 100) {i++;}
				shellcmd[i] = c;
			} while (c != 0);
			
			printf("PID: %d szerver:\n", getpid());
			int hanyan = 0;

			ps = popen(shellcmd, "r");
			do{
				c = fgetc(ps);
				if (c == '\n')
					hanyan++;
				write(szerver_kliens[1], &c, sizeof(char));
			} while (c != EOF);			
			write(users[1], &hanyan, sizeof(int));
			pclose(ps);
			exit(0); //SZERVER FOLYAMATOT ALLITSD LE!!
		}

		default:{ //szulo= kliens
			close(kliens_szerver[0]);
			close(szerver_kliens[1]);
			close(users[1]);
			printf("PID:%d kliens: ", getpid());	
			char c;
			char bemenet[3];
			scanf("%s", bemenet);
			if (atoi(bemenet) < 1 || atoi(bemenet) >= 32)
			{
				printf("Hasznalat: datum(nap)\n");
				exit(1);
			}	

			write(kliens_szerver[1], bemenet, strlen(bemenet)+1);
			wait(NULL);
			int hanyan;
			read(users[0], &hanyan, sizeof(int));//hany ember BEOLVASAS
			printf("%d\n", hanyan);
			int word_count = 0;
			do{
				read(szerver_kliens[0], &c, sizeof(char)); //szerver->kliens VEGEREDMENY KIIRASA
				if (c != EOF){
					word_count++;
					printf("%c", c);
				}
			} while (c != EOF);
			
			if (word_count == 0)
			{
				printf("Ezen a napon nem jelentkezett be meg senki!\n");
			}
			wait(NULL);
			exit(0);
			
		}
	}
	return 0;
}
