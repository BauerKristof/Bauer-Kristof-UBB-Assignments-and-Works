/*
Bauer Kristof
511
Bontsuk törzstényezőkre egy adott természetes számot!
*/

#include <iostream>
#include <fstream>

using namespace std;

void torzstenyezo(int sz)
{
	int oszto = 2; int hatv;

	while (sz != 1)
	{
		hatv = 0;

		while ((sz % oszto) == 0)
		{
			sz = sz / oszto;
			hatv++;
		}

		if (hatv != 0)
		{
			cout << oszto;

			if (hatv > 1)
			{
				cout<<"^" << hatv;
			}

			if (sz != 1) 
			{
				cout << "*";
			}
		}
		oszto++;
	}
}

int main()
{
	ifstream file;
	file.open("bkim1790_L2_8.txt");

	int szam;
	if (file.is_open())
	{
		file >> szam;
	}

	file.close();
	torzstenyezo(szam);
	return 0;
}