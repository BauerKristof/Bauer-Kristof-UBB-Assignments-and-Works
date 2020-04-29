
/* 
Bauer Kristof
511
Írjunk algoritmust, amely megkeresi és kiírja az első n tökéletes számot! Egy szám tökéletes, ha egyenlő a nála kisebb osztóinak összegével.

*/

//

#include <iostream>
#include <fstream>

using namespace std;


int beolvas()
{

	ifstream myfile;
	myfile.open("bkim1790_L2_1.txt");
	int n;

	if (myfile.is_open())
	{
		myfile >> n;
	}

	myfile.close();
	return n;

}



void tokeletesSzam(int n)
{
	int  db = 0;
	long szam = 6;
	long s;
    double ngy=0.0;

	cout << "Az elso " << n << " tokeletes szam: ";
		while (db < n)
		{
			s = 1;
			ngy = sqrt(szam);

			for (long oszto = 2; oszto < ngy; oszto++)
			{
				if ((szam%oszto) == 0)
				{

					s =s+ oszto;

					if (oszto != (szam / oszto))
					{
						s =s+ szam / oszto;
					}
				}
			}

			if (s == szam)
			{
				db++;
				cout << s << ", ";
			}
			szam++;

		}
}

int main()
{
	int n=beolvas();
	tokeletesSzam(n);
	return 0;	
}