/*
Bauer Kristof
511
Adott egy n x n méretű négyzetes tömb. Rendezzük át a tömb oszlopait úgy, hogy az oszlopelemek összege növekvő sorozatot alkosson! A bemenet első sora tartalmazza az n értékét, ezt követően pedig az n x n elemet.
*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int matrix[50][50], int &n)
{
	ifstream file;
	file.open("bkim1790_L3_3.txt");

	if (file.is_open())
	{
		file >> n;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				file >> matrix[i][j];
			}
		}
	}
}

void osszeg(int matrix[50][50],int n, int a[50])
{
	int sum = 0;

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			sum += matrix[i][j];
		}
		a[j] = sum;
		sum = 0;
	}
}


void cserel(int a[50][50], int n, int oszlop1, int oszlop2)
{
	int t= 0;
	for (int i = 0; i < n; i++)
	{
		t = a[i][oszlop1];
		a[i][oszlop1] = a[i][oszlop2];
		a[i][oszlop2] = t;
	}
}

void rendez(int matrix[50][50], int n, int a[50])
{
	int t = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				t = a[i];
				a[i] = a[j];
				a[j] = t;
				cserel(matrix, n, i, j);	
			}
		}
	}
}

void kiirmatrix(int matrix[50][50], int n)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int tores;
	int matrix[50][50];
	int osszegVektor[50], n = 0;

	beolvas(matrix,n);
	kiirmatrix(matrix, n);
	osszeg(matrix, n, osszegVektor);
		
	rendez(matrix, n, osszegVektor);

	kiirmatrix(matrix, n);
	cin >> tores;
	return 0;
}