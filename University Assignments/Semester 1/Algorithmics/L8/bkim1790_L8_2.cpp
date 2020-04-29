/*
Bauer Kristof
511
A kolozsvári színház műsorában n előadás szerepel. 
Mindenik esetében ismert a kezdés időpontja, valamint az előadás végének pontos ideje. Egy különleges vendég kedvéért a színház be szeretné mutatni egyetlen nap folyamán minden előadását. 
Mivel csak egy színhely áll rendelkezésre, állapítsuk meg azt a maximális számú színdarabot, amelyeket a színház bemutathat anélkül, hogy az eredeti kezdési és zárási időpontokat változtatnák.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct eloadasok
{
	int sorszam;
	int kezdido;
	int vegido;
};

void beolvas(eloadasok darabok[100],int &n)
{
	ifstream file;
	file.open("bkim1790_L8_2.txt");


	if (file.is_open())
	{
		file >> n;

		for (int i = 1; i <= n; i++)
		{
			int kora, kperc, vora, vperc;
			char kettospont;
			file >> kora >> kettospont >> kperc>>  vora >> kettospont >> vperc;
			darabok[i].sorszam = i;
			darabok[i].kezdido = kora * 60 + kperc;
			darabok[i].vegido = vora * 60 + vperc;
		}
	}
}

int oszd(eloadasok x[100], int b, int j)
{
	eloadasok d;
	d.sorszam = x[b].sorszam;
	d.kezdido = x[b].kezdido;
	d.vegido = x[b].vegido;
	int k = b;

	while (b < j)
	{
		while ((b < j) && (x[j].vegido >= d.vegido))
		{
			j--;
		}

		x[k].sorszam = x[j].sorszam;
		x[k].kezdido = x[j].kezdido;
		x[k].vegido = x[j].vegido;
		k = j;

		while ((b < j) && (x[b].vegido <= d.vegido))
		{
			b++;
		}
		x[k].sorszam = x[b].sorszam;
		x[k].kezdido = x[b].kezdido;
		x[k].vegido = x[b].vegido;
		k = b;
	}
	x[k].sorszam = d.sorszam;
	x[k].kezdido = d.kezdido;
	x[k].vegido = d.vegido;
	return k;

}

void quick(eloadasok x[100], int bal, int jobb)
{
	int kozep;
	if (bal < jobb)
	{
		kozep = oszd(x, bal, jobb);
		quick(x, bal, kozep - 1);
		quick(x, kozep + 1, jobb);
	}
}

void keres(eloadasok x[100], int n)
{
	int db = 1;
	for (int i = 1; i <n; i++)
	{
		if (x[i].kezdido < x[i + 1].kezdido) 
		{ db++; }
	}

	cout << db << endl;
}


int main()
{
	eloadasok szinhaz[100];
	int n;

	beolvas(szinhaz, n);
	quick(szinhaz, 1, n);
	keres(szinhaz, n);
	system("pause");
	return 0;

}