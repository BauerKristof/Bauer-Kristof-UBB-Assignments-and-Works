/*
Bauer Kristof
511
1. Legyen n természetes szám, állapítsuk meg a számok összegét!
*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int arr[], int &n)
{
	ifstream file;
	file.open("bkim1790_L7_1.txt");
	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >> arr[i];
		}
	}

	file.close();
}

int osszeg(int x[100],int bal, int jobb)
{
	if (bal == jobb)
	{
		return x[bal];
	}
	else if (bal - jobb == 1)
	{
		return (x[bal] + x[jobb]);
	}

	else
	{
		int kozep = (bal + jobb) / 2;
		int szam1=osszeg(x,bal, kozep);
		int szam2=osszeg(x,kozep + 1, jobb);
		return (szam1 + szam2);
	}
}

int main()
{
	int arr[100];
	int n;


	beolvas(arr, n);
	cout << osszeg(arr, 0, n - 1) << endl;
	system("pause");

	return 0;
}