// bkim1790_L2_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Adott egy arab szám (n ≤ 5000), írjuk ki római számjegyekkel!
*/

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

void arabRomai(int arabszam)
{

	int szamertek[] = { 1, 4, 5, 9, 10, 40, 49, 50, 90, 99, 100, 400, 499, 500, 900, 999, 1000 };
	string betuertek[] = { "I","IV","V","IX","X","XL","IL","L","XC","IC","C","CD","ID","D","CM","IM","M" };

	int c = 16;


	while (arabszam > 0)
	{
		if (arabszam >= szamertek[c])
		{
			cout << betuertek[c];
			arabszam -= szamertek[c];
		}
		else
			c--;
	}
}

int main()
{
	ifstream file;
	file.open("bkim1790_L2_7.txt");

	int n;
	if (file.is_open())
	{
		file >> n;
	}
	file.close();

	arabRomai(n);

	return 0;
}

