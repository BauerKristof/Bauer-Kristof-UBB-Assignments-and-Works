/*
Bauer Kristof
511
4. Legyen a következő játék: az egyik játékos (Játékos1) gondol egy 0 és 1000 közötti természetes számra. A másik játékosnak (Játékos2) ki kell találnia ezt a számot minél kevesebb próbálgatással. A titkos szám „birtokosa” (Játékos1) egy-egy találgatásra csak annyit válaszol, hogy a titkos szám kisebb vagy nagyobb
mint a másik játékos (Játékos2) által feltételezett szám.
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>   
#include <time.h>       

using namespace std;

void jatek(int bal,int jobb, int vart)
{

		int kozep = ((bal + jobb) / 2);
		cout << "A robot altal gondolt szam: " << kozep << endl;

		if (vart == kozep)
		{
			cout << "A Robot megtalalta az elemet!" << endl;
			return;
		}
		else
		{
			if (vart < kozep) return jatek(bal, kozep - 1, vart);
			else if (vart > kozep) return jatek(kozep + 1, jobb, vart);
		}
}

int main()
{
	int szam1,szam2;
	cout << "Add meg az alatalad gondolt szamot " << endl;
	cin >> szam1;

	srand(time(NULL));
	szam2= rand() % 1000 + 1;
	cout << "A robot altal gondolt szam: " << szam2<<endl;
	jatek(1, szam2,szam1);
	system("pause");

	return 0;
}