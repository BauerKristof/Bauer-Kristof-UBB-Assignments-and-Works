/*
Bauer Kristof
511
Az egyetem kapott n számítógépet, amelyeket különböző épületekbe és termekbe fognak elhelyezni úgy, hogy a számítógépek egy lineáris hálózatot alkossanak: minden számítógép két másikkal lesz összekötve,
kivéve az elsőt és az utolsót, amelyek csak egy-egy számítógéppel lesznek összekötve.*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct pont
{
	int x;
	int y;
};


void beolvas(pont pontok[], int &n)
{
	ifstream file;
	file.open("bkim1790_L8_8.txt");

	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >> pontok[i].x >> pontok[i].y;
		}
	}

}

void minszamol(pont a[], int n, int reszmeg[], int L[], double &ossz)
{
	int legkozelebbi;

	for (int i = 1; i < n; i++)
	{
		double legkissebb = DBL_MAX;
		for (int j = 0; j < n; j++)
		{
			if (L[j] != 1)
			{
				int kord1 = pow((a[j].x - a[reszmeg[i - 1]].x), 2);
				int kord2 = pow((a[j].y - a[reszmeg[i - 1]].y), 2);
				double fullkolts = sqrt(kord1 + kord2);

				if (fullkolts < legkissebb)
				{
					legkissebb = fullkolts;
					legkozelebbi = j;
					L[legkozelebbi] = 1;
				}
			}
		}
		ossz += legkissebb;
		reszmeg[i] = legkozelebbi;
	}
}

void szamol(pont a[], int n, int eredm[], double &minossz)
{
	int reszmeg[100];
	int L[100];
	double ossz = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) { L[j] = 0; }
		L[i] = 1;
		ossz = 0;
		reszmeg[0] = i;
		minszamol(a, n, reszmeg, L, ossz);

		if (ossz <= minossz)
		{
			minossz = ossz;
			for (int j = 0; j < n; j++)
			{
				eredm[j] = reszmeg[j];
			}
		}
	}

	for (int i = 0; i < n; i++) { eredm[i]++; }

}

void kiir(int eredm[], int n, double minossz)
{

	for (int i = 0; i < n; i++)
	{
		cout << eredm[i] << " ";
	}
	cout << endl;
	cout << minossz << endl;;
}


int main()
{
	int eredm[100], n;
	pont a[100];
	double minosszeg = DBL_MAX;

	beolvas(a, n);
	szamol(a, n, eredm, minosszeg);
	kiir(eredm, n, minosszeg);
	system("pause");
	return 0;
}