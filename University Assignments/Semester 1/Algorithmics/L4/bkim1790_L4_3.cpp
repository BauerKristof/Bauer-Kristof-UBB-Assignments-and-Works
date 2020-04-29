/*
Bauer Kristof
511
Ismerjük egy osztály tanulóinak neveit és év végi átlagait. Állapítsuk meg, hogy egy adott nevű tanuló az első három díjazott között van-e?
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void beolvas(string nevek[], int &n, double jegyek[], string &keresett)
{
	ifstream file;
	file.open("bkim1790_L4_3.txt");

	if (file.is_open())
	{
		string veznev, keresztnev;
		file >> n;
		for (int i = 0; i <= n; i++)
		{
			file >> veznev;
			file >> keresztnev;
			veznev = veznev + ' ' + keresztnev;
			nevek[i] = veznev;
			file >> jegyek[i];
		}

		keresett= veznev;
	}
}

void kiir(string nevek[], int n, double jegyek[])
{
	for (int i = 0; i < n; i++)
	{
		cout << nevek[i] << " " << jegyek[i] << endl;
	}
	cout << endl;
}



void rendez(double jegyek[], int n, string nev[])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (jegyek[i] < jegyek[j])
			{
				swap(jegyek[i], jegyek[j]);
				swap(nev[i], nev[j]);
			}
		}
	}
}

int keres(string nevek[], int n, string keresett)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (nevek[i] == keresett)
		{
			break;
		}
	}

	if (i < n) return i;
	else return -1;
}


int main()
{
	int brk,n;
	string nevek[200],keresett;
	double jegyek[200];
	
	beolvas(nevek, n, jegyek,keresett);
	kiir(nevek, n, jegyek);
	rendez(jegyek, n, nevek);
	kiir(nevek, n, jegyek);

	int poz = keres(nevek, n, keresett);

	if (poz != -1 && poz <= 2)
	{
		cout << "igen";
	}
	else cout << "nem";

	cin >> brk;
	return 0;
}