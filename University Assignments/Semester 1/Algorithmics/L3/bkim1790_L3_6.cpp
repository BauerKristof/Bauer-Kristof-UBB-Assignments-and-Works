/*
Bauer Kristof
511
Egy adott sz�veg szavakat tartalmaz, ismeretlen sz�m� sz�k�zzel elv�lasztva. �rjunk programot, amely t�rli a sz�veg leghosszabb szav�t! T�bb azonos hossz�s�g� sz� eset�n t�r�lj�k mindegyiket! A kimeneti sz�vegben a szavak egy-egy sz�k�zzel legyenek elv�lasztva!
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;



void beolvas(string arr[], int &n)
{
	ifstream f;
	string s;
	

	f.open("bkim1790_L3_6.txt");

	if (f.is_open())
	{
		while (f >> s)
		{
			n++;
			arr[n] = s;
		}
	}
	f.close();
}


void kiir(string arr[], int n)
{
	for (int i = 0; i <= n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void torolElem(string arr[], int  &n, int poz)
{
	for (int i = poz; i <= n - 1; i++)
	{
		arr[i] = arr[i + 1];
	}

	n--;

}

void leghosszabbSzavakTorol(string arr[], int &n)
{
	int max = arr[0].length();
	for (int i = 1; i <= n; i++)
	{
		if ((arr[i].length()) > max)
		{
			max = arr[i].length();
		}
	}

	int i = 0;
	while (i <= n)

	{
		if ((arr[i].length()) == max)
		{
			torolElem(arr, n, i);
		}
		i++;
	}
}

int main()
{
	int tores;
	int n = -1, hanyszor = 0;
	string s[100];

	beolvas(s,n);
	kiir(s, n);
	leghosszabbSzavakTorol(s, n);
	kiir(s, n);
	cin >> tores;

	return 0;
}