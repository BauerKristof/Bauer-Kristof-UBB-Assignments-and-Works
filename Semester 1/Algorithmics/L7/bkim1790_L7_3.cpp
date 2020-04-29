/*
Bauer Kristof
511
3. Adott egy sorozat. Tudva, hogy a sorozat nem rendezett, állapítsunk meg minden olyan helyet, ahol egy adott érték áll.
*/

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;
int max = INT_MIN;

void beolvas(int arr[], int &n, int &szam)
{
	ifstream file;
	file.open("bkim1790_L7_3.txt");
	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >> arr[i];
		}
		file >> szam;
	}

	file.close();
}

void all(int x[100], int bal,int jobb,int szam)
{
	if (bal == jobb)
	{
		if (x[bal] == szam)
		{
			cout << bal+1<<" ";
		}
	}
	else
	{
		if (jobb - bal == 1)
		{
			if (x[bal] == szam) cout << bal+1 << " ";
			if (x[jobb] == szam) cout << jobb+1 << " ";
		}

		else
		{
			int kozep = ((bal + jobb) / 2);

			all(x, bal, kozep, szam);
			all(x, kozep + 1, jobb, szam);
		}
	}
}	

int main()
{
	int arr[100];
	int n,szam;


	beolvas(arr, n,szam);
	all(arr, 0, n - 1, szam);
	cout << endl;
	system("pause");

	return 0;
}