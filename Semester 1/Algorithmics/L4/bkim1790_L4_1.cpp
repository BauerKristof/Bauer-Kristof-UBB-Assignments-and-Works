/*
Bauer Kristof
511
Adott egy programozási verseny eredmény-listája, valamint az a legkisebb pontszám, amellyel be lehet nevezni a következő fordulóra. Hány százalékot képez a következő fordulóra beiratkozók száma?
*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int arr[], int &n, int &pont)
{
	ifstream file;
	file.open("bkim1790_L4_1.txt");

	if (file.is_open())
	{
		file >> n;

		for (int i = 0; i < n; i++)
		{
			file >> arr[i];
		}

		file >> pont;
	}
}

void kiir(int arr[], int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
}

void szamol(int a[], int n, int pont)
{
	int db = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= pont)
		{
			db++;
		}
	}

	cout << "Eredmeny= " << (db * 100) / n;

}



int main()
{
	int brk;

	int a[200];
	int n,pont;

	beolvas(a, n, pont);
	szamol(a, n, pont);

	cin >> brk;
	return 0;
}