/*
Bauer Kristof
511
5.Írjunk programot amely a 4-es feladat játékát szimulálja, úgy, hogy a számítógép a Játékos1, azaz ő generál egy véletlenszerű számot amit a felhasználónak ki kell találnia.
*/


#include <iostream>
#include <fstream>
#include <stdlib.h>   
#include <time.h>       

using namespace std;

void jatek(int jatekostipp, int vart)
{
	if (jatekostipp == vart)
	{
		cout << "Gratulalok, megtalaltad a szamot!" << endl;
		return;
	}

	else
	{
		if (jatekostipp < vart)
		{
			cout << "A robot egy nagyobb szamra gondolt, adj meg egy nagyobb erteket:";
			cin >> jatekostipp;
			cout << endl;
			jatek(jatekostipp, vart);
		}
		else
		{
			cout << "A robot egy kissebb szamra gondolt, adj meg egy kissebb erteket: ";
			cin >> jatekostipp;
			cout << endl;
			jatek(jatekostipp, vart);
		}

	}
}

int main()
{

	int szam1, szam2;
	srand(time(NULL));
	szam2 = rand() % 1000 + 1;
	//cout << "A robot altal gondolt szam: " << szam2 << endl;
	//cout << endl;
	cout << "Add meg az alatalad gondolt szamot 0-1000 kozott" << endl;
	cin >> szam1;

	jatek(szam1,szam2);
	system("pause");

	return 0;
}