/*
Bauer Kristof
511
Adott egy n x n méretű tömb. Határozzuk meg a mellékátló alatti elemek közül a legnagyobbat! A bemenet első sora tartalmazza az n értékét, ezt követően pedig az n x n elemet.

*/

#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

void beolvas(int a[][100], int &n)
{
	ifstream fin;

	fin.open("bkim1790_L3_2.txt");

	if (fin.is_open())
	{
		fin >> n;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				fin >> a[i][j];
			}
		}
	}
	fin.close();
}

void kiir(int a[][100], int n)
{

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

}

int legnagyobb(int a[][100], int n)
{
	int max = a[1][n];

	for (int i = 2; i <= n; i++)
	{
		for (int j = n - i + 2; j <= n; j++)
		{
			if (a[i][j] > max)
			{
				max = a[i][j];
			}
		}
	}

	return max;
}

int main()
{
	int matrix[100][100];
	int n;

	beolvas(matrix, n);
	kiir(matrix, n);
	cout << legnagyobb(matrix, n);

}