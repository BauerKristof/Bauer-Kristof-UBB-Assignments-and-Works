/*Bauer Kristof
511
Írjunk programot, mely kiírja az {1, 2, …, n} halmaz minden permutációját!
*/


#include <iostream>

using namespace std;

int n = 0;
int x[100];

void kiir()
{
	for (int i = 1; i <= n; i++)
	{
		cout << x[i] << " ";
	}
	cout << endl;
}

bool jo(int i)
{
	bool ok = true;

	for (int j = 1; j <= i-1; j++)
	{
		if (x[j] == x[i])
		{
			ok = false;
			break;
		}
	}

	return ok;
}

void back(int i)
{
	for (int j = 1; j <= n; j++)
	{
		x[i] = j;

		if (jo(i))
		{
			if (i == n)
			{
				kiir();
			}
			else back(i + 1);
		}
	}
}

int main()
{
	cout << "n= ";
	cin >> n;
	back(1);
	system("pause");
	return 0;
}