/*
Bauer Kristof
511
Egy utazóügynök házról házra jár az áruival. A cégnek n féle áruja van; minden áru súlyát és árát ismerjük. Tudva azt, hogy az ügynök hátizsákjába legtöbb S súlyú árut lehet becsomagolni, írjuk ki azokat az árukat, amelyeket az ügynök kiválaszt az n áru közül tudva, hogy az áruk értékének legkevesebb Összeg-gel kell egyenlőnek lennie.


*/

#include <iostream>
#include <fstream>

using namespace std;

struct elemtulajd
{
	int hanyadik;
	int suly;
	int ertek;
};

elemtulajd elem[100];
elemtulajd x[100];

int n, minossz = 0, hatizsak = 0;

void beolvas()
{
	ifstream file;
	file.open("bkim1790_L6_06.txt");
	if (file.is_open())
	{
		file >> n >> minossz >> hatizsak;
		for (int i = 1; i <= n; i++)
		{
			file >> elem[i].suly >> elem[i].ertek;
			elem[i].hanyadik = i;
		}
	}

}


void kiir(int m)
{
	for (int i = 1; i <= m; i++)
	{
		cout << x[i].hanyadik << " ";
	}
	cout << endl;

}

bool jo(int m)
{
	bool ok=true;
	for (int i = 1; i <= m-1; i++)
	{
		if (x[i].hanyadik == x[m].hanyadik)
		{
			ok = false;
			break;
		}
	}

	for (int i = 1; i <= m - 1; i++)
	{
		if (x[i].hanyadik > x[i+1].hanyadik) { ok = false; break; }
	}

	return ok;

}

void back(int i, int ossz, int sulya)
{
	for (int j = 1; j <= n; j++)
	{
		x[i] = elem[j];

		if ( jo(i) )
		{
			ossz += x[i].ertek;
			sulya+= x[i].suly;
			
			if ((ossz >= minossz) && (sulya<=hatizsak))
			{
				kiir(i);
			}

			back(i + 1, ossz, sulya);

			ossz -= x[i].ertek;
			sulya -= x[i].suly;
		}
	}

}

int main() 
{
	int osszeges=0, sulyos=0;
	beolvas();
	back(1,osszeges,sulyos);
	system("pause");
}