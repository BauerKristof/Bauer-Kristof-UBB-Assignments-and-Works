/*
Bauer Kristof
511
Számítsuk ki, adott n és x értékekre, a következő összeget:


*/


#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void beolvas(int &n, int &x)
{
	ifstream file;
	file.open("bkim1790_L4_7.txt");

	if (file.is_open())
	{
		file >> n >> x;
	}

}

long faktorialis(int n)
{
	long szam = 1;
	for (int i = 1; i <= n; i++)
	{
		szam *= i;
	}
	return szam;
}

double szamol(int n, int x)
{
	int i = 0;
	double szam = 0;
	double osszeg = 0;
	
	while (i <= n)
	{
		szam = pow(-1, i)* (pow(x, 2 * i) / faktorialis(2 * i));
		osszeg += szam;
		i++;
	}

	return osszeg;
}

int main()
{
	int brk;
	int n, x;
	beolvas(n, x);
	cout<< szamol(n, x)<<endl;

	cin >> brk;
	return 0;

}