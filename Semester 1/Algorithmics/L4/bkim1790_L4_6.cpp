/*
Bauer Kristof
511
Adottak az elsőéves egyetemisták névsorai (abc sorrendben), csoportonként. Állítsunk elő ezekből egyetlen névsort, mely szintén abc sorrendben van!


*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void kiir(string arr[], int n)
{

	for (int i = 0; i <n; i++)
	{
		cout << arr[i] << endl;
	}

	cout << endl;
}


void osszefesul(string x[], int n, string y[], int m, string z[], int &db)
{
	int i = 0;
	int j = 0;
	db = 0;

	while ((i < n) && (j < m))
	{
		if (x[i] < y[j]) 
		{
			z[db] = x[i];
			i++;
		}
		else 
		{
			z[db] = y[j];
			j++;
		}

		db++;
	}

	while (i < n)
	{
		z[db] = x[i];
		db++;
		i++;
	}

	while (j < m) 
	{
		z[db] = y[j];
		db++;
		j++;
	}
}

void felcserel(string a[], int &n, string b[], int m)
{
	n = m;
	for (int i = 0; i < m; i++)
	{
		a[i] = b[i];
	}

}


void beolvas()
{
	ifstream file;
	file.open("bkim1790_L4_6.txt");

	if (file.is_open())
	{
		int ncsop, dbcsop = 2;
		int n, m, k = 0;
		string a[200], b[200], c[200], teljnev;


		file >> ncsop; //csoport szama
		file >> n; // elso csoport
		getline(file, teljnev);
		
		for (int i = 0; i <n; i++)
		{
			getline(file, teljnev);
			a[i] = teljnev;
		}
		file >> m; //masodik csoport

		getline(file, teljnev);
		for (int i = 0; i < m; i++)
		{
			getline(file, teljnev);
			b[i] = teljnev;
		}
		osszefesul(a, n, b, m,c,k);


		while (dbcsop < ncsop)
		{
			file >> m;
			getline(file, teljnev);
			
			for (int i = 0; i <= m; i++)
			{
				getline(file, teljnev);
				b[i] = teljnev;
			}


			osszefesul(c, k, b, m, a, n);
			felcserel(c, k, a, n);
			dbcsop++;
		}


		kiir(c, k);
	}
}


int main()
{
	int brk;
	beolvas();
	cin >> brk;
	return 0;
}
