/*
Bauer Kristof
511
Egy n  m méretű kétdimenziós tömb több tárgy bináris kódját tartalmazza. A tárgynak megfelelő kód 1, a határvonalának megfelelő 0. Állapítsuk meg és írjuk ki minden tárgy esetében egy tetszőleges 1 értékű elemének koordinátáit, valamint a kerületét (azon 0 értékű elemek számát, amelyek a tárgy határvonalán vannak, vagyis vízszintesen vagy függőlegesen, a legközelebb a tárgyhoz).

*/

#include<iostream>
#include<fstream>

using namespace std;

int matrix[100][100];
int kerulet;
int n=0,m=0,db = 0;


void beolvas() 
{
	ifstream file;
	file.open("bkim1790_L6_07.txt");
	if (file.is_open())
	{
		file >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				file >> matrix[i][j];
			}
		}
	}
}



void back(int i, int j) 
{

	if (matrix[i][j] == 1)
	{
		matrix[i][j] = 2;
		kerulet++;
		back(i, j - 1);
		back(i, j + 1);
		back(i + 1, j - 1);
		back(i + 1, j);
		back(i + 1, j + 1);
		back(i - 1, j - 1);
		back(i - 1, j);
		back(i - 1, j + 1);
	}
}

void keres()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (matrix[i][j] == 1)
			{
				kerulet = 0;
				back(i, j);
				db++;
				cout << db << "-es targy: Koordinata: (" << i << ", " << j << ") " << ", Kerulet= " << kerulet << endl;
			}
}

int main() 
{
	beolvas();
	keres();
	system("pause");
}