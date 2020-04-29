/*
Bauer Kristof
511
A karácsonyi vásáron m áruházban n különböző terméket árusítanak ...
*/

#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

void beolvas(int a[][100], int &m, int &n, int &termek, int &bolt)
{
	ifstream fin;

	fin.open("bkim1790_L3_1.txt");

	if (fin.is_open())
	{
		fin >> m >> n;

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				fin >> a[i][j];
			}
		}

		fin >> termek >> bolt;


	}

}

void kiir(int a[][100], int m, int n)
{

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

}

int legmagasabbAtlagar(int a[][100], int m, int n)
{
	double maxatl = 0, sum = 0;
	int sorszam;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			sum += a[i][j];
		}

		if ((sum / 3) > maxatl)
		{
			maxatl = sum / 3;
			sorszam = i;
		}

		sum = 0;
	}

	return sorszam;
}

void legolcsobbAruSorszama(int a[][100], int m, int n)
{
	int min = a[1][1];

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] < min)
			{
				min = a[i][j];
			}
		}
	}


	cout << "A legolcsobb termekek : ";


	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] == min)
			{
				cout << j << " ";
			}
		}
	}

	cout << endl;

}

void legolcsobbdragabb(int a[][100], int m, int n, int termek)
{
	int min = a[1][termek], minAruhaz = 1;
	int max = a[1][termek], maxAruhaz = 1;

	for (int i = 1; i <= m; i++)
	{
		if (a[i][termek] < min)
		{
			min = a[i][termek];
			minAruhaz = i;
		}

		if (a[i][termek] > max)
		{
			max = a[i][termek];
			maxAruhaz = i;
		}

	}

	cout << "Az " << termek << " sorszamu termeket a legolcsobban az " << minAruhaz << " legdragabban pedig a " << maxAruhaz << " aruhazban lehet megtalalni." << endl;
}


void atlBolt(int a[][100], int m, int n, int atlbolt)
{
	float atl = 0.0;

	for (int j = 1; j <= n; j++)
	{
		atl += a[atlbolt][j];
	}

	cout << "A " << atlbolt << ". sorszamu aruhaz termekeinek atlagara ";
	printf("%.2f\n", atl / n);

}

int main()
{
	int brk;
	int matrix[100][100];
	int m, n, termek, atlbolt;

	beolvas(matrix, m, n, termek, atlbolt);
	kiir(matrix, m, n);
	

	cout << "A legmagasabb atlagaru aruhaz :" << legmagasabbAtlagar(matrix, m, n) << endl;

	legolcsobbAruSorszama(matrix, m, n);
	legolcsobbdragabb(matrix, m, n, termek);
	atlBolt(matrix, m, n, atlbolt);

	cin >> brk;

	return 0;
}