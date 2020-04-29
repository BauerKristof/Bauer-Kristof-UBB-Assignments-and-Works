/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely kiszámítja n természetes szám legnagyobb közös osztóját!

*/


#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int arr[], int &n)
{
	ifstream file;
	file.open("bkim1790_L5_4.txt");
	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i <= n; i++)
		{
			file >> arr[i];
		}

	}

}

int lnko(int a, int b) 
{
	if (a == b)
	{
		return b;
	}
	else
	{
		if (a > b) return lnko(a - b, b);
		else return lnko(a, b - a);
	}
}

int soklnko(int arr[], int n, int vlnko)
{

	if (n == 0) return vlnko;
	else
	{
		int vlnko = lnko(arr[n], arr[n - 1]);
		return soklnko(arr, n - 2, vlnko);
	}
}


int main()
{
	int a[100], n,vlnko=1;
	beolvas(a, n);
	cout << soklnko(a,n-1,vlnko) << endl;
	system("PAUSE");
	return 0;

}