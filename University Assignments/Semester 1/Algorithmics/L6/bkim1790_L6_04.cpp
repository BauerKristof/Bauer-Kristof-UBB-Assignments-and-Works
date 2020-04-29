/*
Bauer Kristof
511
Legyen n építőkocka, amelyek 1-től n-ig vannak címkézve. 
Beolvassuk az oldalaik hosszát és a színüket. 
Írjunk ki minden k kockából álló tornyot, amelyeket úgy építhetünk fel, hogy nem teszünk egymásra azonos 
színű kockát és oldalaik mérete (lentről felfele)csökkenő sorozatot alkotnak.


*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct tulajdonsag
{
	int hanyadik;
	string szin;
	int hossz;
};

int n = 0;
int k = 0;
tulajdonsag szam[100];
tulajdonsag x[100];

void beolvas()
{
	ifstream file;
	file.open("bkim1790_L6_04.txt");

	if (file.is_open())
	{
		file >> n;
		file >> k;

		for (int i = 1; i <= n; i++)
		{
			file >> szam[i].szin >> szam[i].hossz;
			szam[i].hanyadik = i;
		}
		file >> k;
	}
}

bool jo(tulajdonsag teszt, int m)
{
	int i = 1;
	bool ok=true;

	while(i<=m-1)
	{
		if (x[i].szin == teszt.szin) 
		{
			ok = false;
		}

		if (x[i].hossz < teszt.hossz)
		{
			ok = false;
		}
		i++;
	}
	
	return ok;
}

void kiir()
{
	for (int i = 1; i <= k; i++)
	{
		cout << x[i].hanyadik<<" ";
	}
	cout << endl;
}

void back(int i)
{
	for (int j = 1; j <= n; j++)
	{
		x[i] = szam[j];

		if (jo(x[i], i) == true)
		{
			if (i == k)
			{
				kiir();
			}
			else back(i + 1);
		}
	}
}

int main()
{
	beolvas();

	back(1);

	system("pause");
	return 0;
}