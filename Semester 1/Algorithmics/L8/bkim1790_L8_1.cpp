/*
Bauer Kristof
511
1.Legyen két, egész számokat tartalmazó halmaz: A = {a1, a2, ..., am} és B = {b1, b2, …, bn} (1  m  n  100).
Határozzuk meg a B halmaz azon X = {x1, x2, …, xm} részhalmazát, amelynek megfelelően az E = a1x1 + a2x2 + … + amxm kifejezés értéke a lehető legnagyobb. 
A bemenet szerkezete: m értéke, A elemei, n értéke, B elemei. A kimenet a maximális értéket kell tartalmazza.


*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int a[100], int b[100], int &n, int &m)
{
	ifstream file;
	file.open("bkim1790_L8_1.txt");

	if (file.is_open())
	{
		file >> m;
		for (int i = 1; i <= m; i++)
		{
			file >> a[i];
		}

		file >> n;

		for (int i = 1; i <= n; i++)
		{
			file >> b[i];
		}

	}
}

int oszd(int x[100], int b, int j)
{
	int d = x[b], k = b;

	while (b < j)
	{
		while ((b < j) && (x[j] >= d))
		{
			j--;
		}

		x[k] = x[j];
		k = j;

		while ((b < j) && (x[b] <= d))
		{
			b++;
		}
		x[k] = x[b];
		k = b;
	}
	x[k] = d;
	return k;

}

void quick(int x[100], int bal, int jobb)
{
	int kozep;
	if (bal < jobb)
	{
		kozep = oszd(x, bal, jobb);
		quick(x, bal, kozep - 1);
		quick(x, kozep + 1, jobb);
	}
}

void szamol(int a[],int m, int b[], int n)
{
	int szorzat = 0;
	int bbal = 1, bjobb=n;
	for (int i = m; i >=1; i--)
	{
			if (a[i] < 0)
			{
				szorzat = szorzat + a[i] * b[bbal];
				bbal++;
			}
			else
			{
				szorzat = szorzat + a[i] * b[bjobb];
				bjobb--;
			}
	}

	cout << szorzat<<endl;
}

int main()
{
	int a[100], b[100], m, n;
	beolvas(a, b, n, m);
	quick(a, 1, m);
	quick(b, 1, n);
	szamol(a, m, b, n);
	system("pause");
	return 0;

}