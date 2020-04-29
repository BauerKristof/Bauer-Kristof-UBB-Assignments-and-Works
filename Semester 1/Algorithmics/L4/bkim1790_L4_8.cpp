/*
Bauer Kristof
511
Két természetes számot rokonnak nevezünk, ha van legalább két (különböző) közös számjegyük. Döntsük el adott két számról, hogy rokonok-e vagy sem!
*/


#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void beolvas(long &a,long &b)
{
	ifstream file;
	file.open("bkim1790_L4_8.txt");

	if (file.is_open())
	{
		file >> a;
		file >> b;
	}

}

bool rokon(long a, long b)
{
	bool seged1[9],seged2[9];

	for (int i = 0; i < 9; i++)
	{
		seged1[i] = false;
		seged2[i] = false;
	}

	while (a != 0)
	{
		seged1[a % 10] = true;
		a /= 10;
	}

	while (b != 0)
	{
		seged2[b % 10] = true;
		b /= 10;
	}

	int db = 0, i = 0;

	while ((i < 9) && (db < 2))
	{
		if ((seged1[i] == true) && (seged2[i] == true))
		{
			db++;
		}
		i++;
	}

	if (db == 2)
	{
		return true;
	}
	else { return false; }
}

int main()
{
	int brk;
	long a, b;
	beolvas(a, b);
	if (rokon(a, b) == 0) { cout << "nem"; }
	else { cout << "igen"; }

	cin >> brk;
	return 0;

}