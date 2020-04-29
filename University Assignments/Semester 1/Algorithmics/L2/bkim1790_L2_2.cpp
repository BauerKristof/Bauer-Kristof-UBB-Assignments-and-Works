// bkim1790_L2_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Határozzuk meg az 1 milliónál kisebb, legnagyobb prímszámot!


*/

#include <iostream>

using namespace std;

bool primSzita(long n)
{
	bool prim[1000001];
	prim[1] = true;
	for (long i = 2; i < n; i++)
	{
		prim[i] = false;
	}



	for (long i = 2; i < (n / 2); i++)
	{
		if (prim[i] == 0)
		{
			long j = i + i;

			while (j <= n)
			{
				prim[j] = true;
				j = j + i;
			}
		}
	}

	if (prim[n] == true) { return false; }
	else { return true; }
}

void kiirSzam()
{
	long i = 1000000;
	while (primSzita(i) == false)
	{
		i--;
	}

	cout << i;

}

int main()
{
	kiirSzam();
	return 0;
}
