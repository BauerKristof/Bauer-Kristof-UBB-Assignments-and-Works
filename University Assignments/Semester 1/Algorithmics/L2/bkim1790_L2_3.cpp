// bkim1790_L2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Írjunk algoritmust, amely megkeresi és kiírja az első n ikerprímet! Két prímszám, p és q ikerprímek, ha |q – p| = 2.

*/

#include <iostream>
#include <fstream>

using namespace std;

int beolvas()
{
	ifstream file;
	file.open("bkim1790_L2_3.txt");

	int n;

	if (file.is_open())
	{
		file >> n;
	}

	file.close();
	return n;
}

bool prim(long n)
{
	bool x[1000000];
	x[1] == true;

	for (long i = 2; i < n; i++)
	{
		x[i] = false;
	}

	for (long i = 2; i < (n/2); i++)
	{
		if (x[i] == false)
		{
			long j = i + i;

			while (j <= n)
			{
				x[j] = true;
				j = j + i;
			}
		}
	}

	if (x[n] == true) return false;
	else return true;
}

void primParok(int n)
{
	int db = 0,i = 3;

	cout << "Az elso " << n << " ikerprim: ";
	while (db < n)
	{
		if (prim(i) == true && prim(i + 2) == true)
		{
			cout << "(" << i << "," << i + 2 << "), ";
			db++;
		}
		i += 2;
	}

}

int main()
{
	int n = beolvas();
	primParok(n);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
