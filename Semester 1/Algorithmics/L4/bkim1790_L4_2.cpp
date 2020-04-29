/*
Bauer Kristof
511
Számoljuk meg egy adott szövegben a magánhangzók számát!
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string beolvas()
{
	ifstream file;
	file.open("bkim1790_L4_2.txt");
	string pots, s;

	if (file.is_open())
	{
		while (file >> pots)
		{
			s = s + pots;
		}	
	}
	return s;
}


int szamol(string s)
{
	int hossz = s.length();
	int	db = 0;

	for (int i = 0; i < hossz; i++)
	{
		char c = toupper(s[i]);
		if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
		{
			db++;
		}
	}

	return db;

}



int main()
{
	int brk;

	string s;
	s=beolvas();
	cout<<szamol(s);

	cin >> brk;
	return 0;
}