/*Nev:Bauer Kristof
Csoport:511*/

#include <iostream>

using namespace std;

void init(char *, char*);
void kiir();
void felsz();
void nagybetuhaelso();


int main()
{
	char veznev[] = "NAGY";
	char kernev[] = "Abel";
	
	init(veznev,kernev);
	kiir();
	nagybetuhaelso();
	kiir();
	felsz();

	
	system("pause");
	return 0;
}