/*
Bauer Kristof
511
Adott egy n elemű, egész számokból álló sorozat. Írjunk programot, amely szétrendezi a sorozatot! Szétrendezés alatt azt a műveletsort értjük, amelynek elvégzése után a legkisebb elem az első helyen, 
az érték szerint következő az utolsó helyen stb. helyezkedik el. A szétrendezést orgonasíp-rendezésnek is nevezzük. A bemenet első sora tartalmazza az n értékét, ezt követően pedig az n elemet.
A kimenet a szétrendezett sorozatot tartalmazza.
*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int arr[],int &n)
{
	ifstream file;
	file.open("bkim1790_L3_4.txt");

	if (file.is_open())
	{
		file >> n;
	}

	for (int i = 1; i <= n; i++)
	{
		file >> arr[i];
	}
}

void quickSort(int arr[], int bal, int jobb)
{

	int i = bal, j = jobb;

	int elem;

	int pivot = arr[(bal + jobb) / 2];

	while (i <= j) 
	{

		while (arr[i] < pivot) i++;

		while (arr[j] > pivot) j--;

		if (i <= j) 
		{

			elem = arr[i];
			arr[i] = arr[j];
			arr[j] = elem;
			i++;
			j--;

		}

	}

	if (bal < j) quickSort(arr, bal, j);

	if (i < jobb) quickSort(arr, i, jobb);

}

void kiir(int arr[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

}

void orgonaSip(int arr[], int n)
{
	int orgona[100];

	int i = 1, e = 1, v = n;

	while (i <= n)
	{
		if (i % 2 != 0)
		{
			orgona[e] = arr[i];
			e++;
		}
		else
		{
			orgona[v] = arr[i];
			v--;
		}

		i++;
	}

	kiir(orgona, n);
}

int main()
{
	int n=0, arr[100],tores;
	beolvas(arr, n);
	kiir(arr, n);
	quickSort(arr, 1, n);
	orgonaSip(arr, n);
	cin >> tores;
	return 0;
}