/*Nev:Bauer Kristof
Csoport:511*/

#include <iostream>

using namespace std;

namespace nevek
{
	char *csnev;
	char *knev;

	void init(char *cs, char *kernev);
	void felsz();
	void nagybetuhaelso();
	void kiir();
}

void nevek::init(char *cs, char *kernev)
{
	csnev = new char[strlen(cs) + 1];

	for (int i = 0; i < strlen(cs) + 1; i++)
	{
		csnev[i] = cs[i];
	}

	//strcpy(csnev, cs);

	knev = new char[strlen(kernev) + 1];
	//strcpy(knev, kernev);

	for (int i = 0; i < strlen(kernev) + 1; i++)
	{
		knev[i] = kernev[i];
	}
}

void nevek::felsz()
{
	delete[] knev;
	delete[] csnev;
}

void nevek::kiir()
{
	for (int i = 0; i < sizeof(csnev); i++)
	{
		cout << csnev[i];
	}
	cout << " ";


	for (int i = 0; i < sizeof(knev); i++)
	{
		cout << knev[i];
	}
	cout << endl;
}

void nevek::nagybetuhaelso()
{
	csnev[0] = toupper(csnev[0]);

	for (int i = 1; i < sizeof(csnev); i++)
	{
		csnev[i] = tolower(csnev[i]);
	}

	knev[0] = toupper(knev[0]);

	for (int i = 1; i < sizeof(knev); i++)
	{
		knev[i] = tolower(knev[i]);
	}
}

int main()
{
	char veznev[] = "NAGY";
	char kernev[] = "Abel";

	nevek::init(veznev, kernev);
	nevek::kiir();
	nevek::nagybetuhaelso();
	nevek::kiir();
	nevek::felsz();


	system("pause");
	return 0;
}