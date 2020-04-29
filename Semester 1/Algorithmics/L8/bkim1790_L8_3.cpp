/*
Bauer Kristof
511
Adott n zeneszámot tartalmazó állomány hossza. Ezeket az állományokat ugyanazon a mágnes szalagon szeretnénk tárolni. 
Állapítsuk meg az állományok optimális elrendezését a szalagon ahhoz, hogy az átlagos elérési idő a lehető legkisebb legyen. 
A bemenet első sora a zeneszámok számát és azok hosszát tartalmazza. A kimenet az állományok optimális elrendezését tartalmazza.
*/

#include <iostream>
#include <fstream>

using namespace std;

struct zene
{
	int sorszam;
	int hossz;
};

void beolvas(zene a[100], int &n)
{
	ifstream file;
	file.open("bkim1790_L8_3.txt");

	if (file.is_open())
	{
		file >> n;
		for (int i = 1; i <= n; i++)
		{
			file >> a[i].hossz;
			a[i].sorszam = i;
		}

	}
}

int oszd(zene x[100], int b, int j)
{
	zene d;
	d.hossz = x[b].hossz;
		d.sorszam = x[b].sorszam;
	int k = b;

	while (b < j)
	{
		while ((b < j) && (x[j].hossz >= d.hossz))
		{
			j--;
		}

		x[k].hossz = x[j].hossz;
		x[k].sorszam = x[j].sorszam;
		k = j;

		while ((b < j) && (x[b].hossz<= d.hossz))
		{
			b++;
		}
		x[k].hossz= x[b].hossz;
		x[k].sorszam = x[b].sorszam;
		k = b;
	}
	x[k].hossz = d.hossz;
	x[k].sorszam = d.sorszam;
	return k;

}

void quick(zene x[100], int bal, int jobb)
{
	int kozep;
	if (bal < jobb)
	{
		kozep = oszd(x, bal, jobb);
		quick(x, bal, kozep - 1);
		quick(x, kozep + 1, jobb);
	}
}



int main()
{
	zene a[100];
	int n = 0;

	beolvas(a, n);
	quick(a, 1, n);

	for (int i = 1; i <= n; i++)
	{
		cout << a[i].sorszam << " ";
	}
	system("pause");
	return 0;

}