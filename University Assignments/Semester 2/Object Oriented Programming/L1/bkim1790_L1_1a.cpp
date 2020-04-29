/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include <stdlib.h> 
#include <time.h>  


using namespace std;


int veletlen_szam(int a, int b)
{
	srand(time(NULL));
	return  (rand() % b-a+1) + a;
}

void jatek(int generaltSzam)
{

	int tipp;
	cout << "Add meg a tipped:";
	cin >> tipp;

	while (tipp != generaltSzam)
	{

		if (tipp > generaltSzam)
		{
			cout << "Kisebb" << endl;
		}

		if (tipp < generaltSzam)
		{
			cout << "Nagyobb" << endl;
		}

		cout << "Add meg a kovetkezo tipped:";
		cin >> tipp;
	}

	cout << "Gratulalok eltalaltad a szamot" << endl;
}

int main()
{
	jatek(veletlen_szam(1, 100));
	system("pause");
	return 0;
}

