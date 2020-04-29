/*Bauer Kristof
511
Adva van n + 1 cipősdoboz és n pár cipő, amelyek meg vannak számozva 1-től n-ig.
Az n pár cipő n+1 dobozban található, a dobozok közül az utolsó üres. 
El kell rendezni a cipőket úgy, hogy minden cipő a megadott dobozba kerüljön.
Munka közben csak egy pár cipőt szabad kivenni a dobozból, amelyben található, és azonnal be kell tenni az üres dobozba. 
Állapítsuk meg a költöztetések sorozatát minimális számú művelettel. A bemenet első sora a cipők számát tartalmazza ...etc

*/

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int db = 0;

void beolvas(int a[100],int &n)
{
	ifstream file;
	file.open("bkim1790_L8_6.txt");

	if (file.is_open())
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >> a[i];
		}
	}
}


void szamol(int a[], int n)
{
	int i = 0;
	while( (i<n) && a[i]==i)
	{
		i++;
	}

	if (i < n)
	{
		a[n] = a[i];
		a[i] = INT_MIN;

		while (a[n] != INT_MIN)
		{
			int j = 0;
			while ((j <= n) && a[j] != i)
			{
				j++;
			}

			db++;
			a[i] = a[j];
			i = j;
			a[i] = INT_MIN;
		}
	}
}

int main()
{
	int a[100], n;
	beolvas(a, n);
	szamol(a, n);
	cout << db << endl;
	system("pause");
	return 0;

}