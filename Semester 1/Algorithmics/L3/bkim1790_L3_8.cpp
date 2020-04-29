/*
Bauer Kristof
511
Adva van több valós együtthatójú polinom. A polinomok száma ismeretlen. Írjunk programot, amellyel kiszámítjuk az összegüket, és kiválasztjuk azt a polinomot, amelynek az a pontban kiszámított értéke
a legnagyobb az összes megadott polinom ugyanazon a pontban kiszámított értékei között.


*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath> //compiler miatt

using namespace std;


void kiirPol(double osszegPol[], int maxegyutthato)
{
	for (int i = maxegyutthato; i >= 0; i--)
	{
		if (osszegPol[i] != 0)
		{
			if (osszegPol[i] > 0)
			{
				cout << "+";
			}
			
			cout << osszegPol[i] << "*X^" << i;
		}
	}
}

void beolvas(double arr[50][50],int &m, int &n, int &a)
{
	ifstream f;

	f.open("bkim1790_L3_8.txt");

	double osszegPol[50];
	int polSzam = 0, maxegyutthato = 0;

	for (int i = 0; i < 50; i++)
	{
		osszegPol[i] = 0;
	}

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			arr[i][j] = 0;
		}
	}



	if (f.is_open())
	{

		f >> a;

		double szam;
		while (f >> szam)
		{
			polSzam++;
			int egyutthato = szam;
			if (egyutthato > maxegyutthato) { maxegyutthato = egyutthato; }
			for (int j = egyutthato; j >= 0; j--)
			{
				double szam;
				f >> szam;
				osszegPol[j] = osszegPol[j] + szam; //vegosszeget szamolo vektor
				arr[polSzam][j] = szam; //berakjuk a matrixba a polinomot
			}
		}

			
	}

	m = polSzam;
	n = maxegyutthato;

	kiirPol(osszegPol, maxegyutthato);
	f.close();
}

int osszSzamit(double arr[50][50], int m, int n, int a, int &sum)
{
	sum = 0;
	int maxsum=0,sor=0;


	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			sum = sum + arr[i][j] * pow(a, j);
		}
		if (sum > maxsum)
		{
			maxsum = sum;
			sor = i;
		}
		sum = 0;
	}

	sum = maxsum;
	return sor;


}

void kiirMatrix(double matrix[50][50], int m, int n)
{
	cout << "M= " << m << "N= " << n << endl;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << matrix[i][j] << " ";
		}cout << endl;
	}
}

void legnagyobbPol(double matrix[50][50],int m, int n, int sor)
{
	for (int i = sor; i < m; i++)
	{
		for (int j = n; j >0; j--)
		{

			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] > 0)
				{
					cout << "+";
				}

				cout << matrix[i][j] << "*X^" << j;
			}
		}

	}
}


int main()
{
	int brk;
	double polMatrix[50][50];
	int a,m,n;
	int poz = 0,ossz=0;

		beolvas(polMatrix,m,n, a);
		cout << endl;
		poz = osszSzamit(polMatrix, m, n,a, ossz);
		legnagyobbPol(polMatrix,m,n, poz);
		cout << endl;
		cout << ossz;

	


	cin >> brk;

	return 0;
}