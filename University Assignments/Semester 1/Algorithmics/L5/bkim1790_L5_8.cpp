/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely generálja egy adott n szám minden partícióját. Azok közül a partíciók közül, amelyek csak a tagok sorrendjében különböznek, csak egyet kell kiírnunk.
*/



#include <iostream>
#include <fstream>

using namespace std;

int p[20];
int n;

void beolvas(int &n)
{
	ifstream file;
	file.open("bkim1790_L5_8.txt");
	if (file.is_open())
	{
		file >> n;
	}

}

void kiir(int i) 
{
	if (i != 1)
	{
		for (int j = i; j >= 1; j--)
		{
			cout << " " << p[j];
		}
		cout << endl;
	}
}

void particio(int i, int n) 
{
	for (int j = 1; j <= n; j++) 
	{
		if (j >= p[i - 1]) 
		{
			p[i] = j;
			if (j < n)	particio(i + 1, n - j);
			else kiir(i);
		}
	}
}



int main()
{
	beolvas(n);
	particio(1, n);
	system("PAUSE");
	return 0;

}