/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely kiszámítja egy n-ed fokú polinom értékét egy adott x pontban!
*/



#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int arr[],int &n, int &x)
{
	ifstream file;
	file.open("bkim1790_L5_3.txt");
	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i<=n; i++)
		{
			file >> arr[i];
		}

		file >> x;

	}

}

int polossz(int arr[], int n, int x)
{
	if (n == 0)
	{
		return arr[0];
	}
	else
	{
		return polossz(arr, n - 1, x) *x+ arr[n];
	}
}


int main()
{
	int a[100],n, x;
	beolvas(a,n,x);
	cout << polossz(a, n, x) << endl;
	system("PAUSE");
	return 0;

}