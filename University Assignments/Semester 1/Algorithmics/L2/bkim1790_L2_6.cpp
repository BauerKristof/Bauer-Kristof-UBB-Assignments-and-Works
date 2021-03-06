// bkim1790_L2_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Adott egy római szám, írjuk ki arab számjegyekkel!
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int szamertek(char betuertek)
	{
		switch (betuertek)
		{
		case 'I':return 1;
		case 'V':return 5;
		case 'X':return 10;
		case 'L':return 50;
		case 'C':return 100;
		case 'D':return 500;
		case 'M':return 1000;
		}
	}

int romaiArab(string romai)
	{
		int i, sum = 0, p = 0;
		int n = romai.length() - 1;

		for (i = n; i >= 0; i--)
		{
			if (szamertek(romai[i]) >= p)
			{
				sum = sum + szamertek(romai[i]);
			}
			else
			{
				sum = sum - szamertek(romai[i]);
			}
			p = szamertek(romai[i]);
		}
		return sum;
	}

int main()
{
	string romai;
	ifstream file;

	file.open("bkim1790_L2_6.txt");

	if (file.is_open())
	{
		file >> romai;
	}

	file.close();

	cout<< romaiArab(romai);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
