/*
Bauer Kristof
511
Adott egy n elemű természetes számokat tartalmazó sorozat. Keressük meg és írjuk ki azt a leghosszabb sb, sb+1, …, sj tömbszakaszt, amely csak prímszámokat tartalmaz! 
A bemenet első sora tartalmazza az n értékét, ezt követően pedig az n elemet.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void beolvas(int arr[], int &n)
{
	ifstream f;

	f.open("bkim1790_L3_7.txt");

	if (f.is_open())
	{
	
		f >> n;

		for (int i = 0; i < n; i++)
		{
			f >> arr[i];
		}
	}

	f.close();
}



void kiir(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout<< arr[i] << " ";
	}
	cout << endl;
}


bool prim(int x) 
{
	if (x <= 1) return 0;
	if (x == 2 || x == 3 || x == 5) return 1;
	if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0) return 0;
	if ((x - 1) % 6 && (x + 1) % 6) return 0;

	int oszto = 6;     
	while (oszto*oszto <= x) 
	{
		if (x % (oszto - 1) == 0 || x % (oszto + 1) == 0)
		{
			return 0;
		}
		oszto += 6;
	}
	return 1;

}

void reszsorozat(int a[], int n, int &kezd, int &vege)
{
	int i = 0, akt = 0,maxhossz=0;

	while (i < n)
	{
		akt = i;
		
		while (prim(a[i]) && (i < n))
		{
			i++;
		}

		if ((i - akt) > maxhossz)
		{
			maxhossz = i - akt;
			kezd = akt;
			vege = i;
		}

		i++;
	}

}

int main()
{
	int brk;
	int a[100], n;
	beolvas(a, n);
	kiir(a, n);
	int kezd, veg;
	
	reszsorozat(a, n, kezd, veg);

	for (int i = kezd; i < veg; i++)
	{
		cout << a[i] << " ";
	}

	cin >> brk;

	return 0;
}