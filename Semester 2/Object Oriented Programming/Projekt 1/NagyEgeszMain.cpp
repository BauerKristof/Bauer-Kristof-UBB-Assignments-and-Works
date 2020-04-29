/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include "NagyEgesz.h"
using namespace std;

int main()
{
	int szam1[] = { 8,9,4,5,8};
	int szam2[] = { 5,0,3};
	NagyEgesz nszam1(1, 5, szam1);
	nszam1.kiir();
	NagyEgesz nszam2(1, 3, szam2);
	nszam2.kiir();
	cout << endl;
	
	nszam1.osszead(nszam2).kiir();
	nszam1.kivon(nszam2).kiir();
	nszam1.szoroz(nszam2).kiir();
	try 
	{
		nszam1.oszt(nszam2).kiir();
	}
	catch (NagyEgesz::NullavalValoOsztas) 
	{
		cout << "HIBA:Nullaval valo osztas!" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}