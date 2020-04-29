/*
Bauer Kristof
511
Ismerjük két szám prímszám osztóit. Határozzuk meg a két szám legkisebb közös többszörösének prímszám osztóit! (A két számot nem ismerjük, csupán a prim osztóikat)

*/

#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

const int MAXINT = INT_MAX;

void beolvas(int arr[], int &n,int arr2[],int &m)
{
	ifstream file;
	file.open("bkim1790_L4_5.txt");

	if (file.is_open())
	{

		string s;
		getline(file, s);

		istringstream iss(s);
		int szam;
		while (iss >> szam) 
		{
			arr[n] = szam;			
			n++;

		}

		getline(file, s);

		istringstream is(s);
		while (is >> szam)
		{
			arr2[m] = szam;
			m++;

		}

	}
}

void kiir(int arr[], int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
}

void osszefesul(int arr[], int n, int arr2[], int m, int z[], int & db)
{
	int i = 0;
	int j = 0;
	db = 0;

	arr[n] = MAXINT;
	arr2[m] = MAXINT;

	while ((i < n) || (j < m)) 
	{
		if (arr[i] < arr2[j]) 
		{
			z[db] = arr[i];
			i++;
		}
		else 
		{
			if (arr[i] == arr2[j])
			{
				z[db] = arr[i];
				i++;
				j++;
			}
			else
			{
				z[db] = arr2[j];
				j++;
			}
		}

		db++;
	}
}


int main()
{
	int brk;

	int a[200],b[200],c[200];
	int n = 0, m = 0,k;

	beolvas(a, n, b,m);
	kiir(a, n);
	kiir(b, m);
	osszefesul(a, n, b, m, c, k);
	kiir(c, k);

	cin >> brk;
	return 0;
}