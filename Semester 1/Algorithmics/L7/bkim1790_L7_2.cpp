/*
Bauer Kristof
511
2. Legyen n természetes szám. Határozzuk meg a számok legkisebb és legnagyobb elemét egyidőben.
*/

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;
int max = INT_MIN;

void beolvas(int arr[], int &n)
{
	ifstream file;
	file.open("bkim1790_L7_2.txt");
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

int min(int x[100], int bal, int jobb)
{
	if (bal == jobb)
	{
		if (x[bal] > max) { max = x[bal]; }
		return x[bal];
	}
	else if (bal - jobb == 1)
	{
		if (x[bal] < x[jobb])
		{
			if (x[jobb] > max) { max = x[jobb]; }
			return x[bal];
		}
		else return x[jobb];
	}

	else
	{
		int kozep = (bal + jobb) / 2;
		int szam1 = min(x, bal, kozep);
		int szam2 = min(x, kozep + 1, jobb);
		if (szam1 < szam2)
		{
			return szam1;
		}
		else return szam2;

	}
}

int main()
{
	int arr[100];
	int n;


	beolvas(arr, n);
	cout <<"Min: " <<min(arr, 0, n - 1) << endl;
	cout << "Max: " << max << endl;
	system("pause");

	return 0;
}