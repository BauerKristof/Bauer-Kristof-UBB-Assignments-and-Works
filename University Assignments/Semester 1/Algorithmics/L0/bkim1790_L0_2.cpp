// bkim1790_l0_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*Hallgató neve: Bauer Kristóf 
Csoport:511
Egy mezőn n ló és m szekér található.  Az i. ló ereje pi, az i. szekér súlya gi. Egy ló legtöbb egy szekeret húzhat, de ennek a súlya kisebb vagy egyenlő a ló erejével. Határozzátok meg a lehetséges legnagyobb ló-szekér párt úgy, hogy a párban szereplő ló legyen képes húzni a megfelelő szekeret.
*/

#include "pch.h"
#include <iostream>

using namespace std;

void rendez(int a[], int n);

int main()
{
	int n = 0, m = 0;
	cout << "n" << endl;
	cin >> n;
	cout << "m" << endl;
	cin >> m;

	int l[1000],sz[1000];

	for (int i = 0; i < n; i++)
	{
		cout << "Lo ereje" << endl;
		cin >> l[i];
	}

	for (int i = 0; i < m; i++)
	{
		cout << "Szeker sulya" << endl;
		cin >> sz[i];
	}

	rendez(l, n);
	rendez(sz, m);

	int db = 0, i = 0, j = 0;

	while ((i < n) && (j < m))
	{
		if (l[i] >= sz[j])
		{
			i++;
			j++;
			db++;
		}
		else
		{
			i++;
		}
	}

	cout << db;
}


void rendez(int a[], int n)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
}