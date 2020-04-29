/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely átalakít egy, a 16-os számrendszerben megadott számot a 10-es számrendszerbe!

*/




#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void beolvas(string &n)
{
	ifstream file;
	file.open("bkim1790_L5_7.txt");
	if (file.is_open())
	{
		file >> n;
	}

}

long konv(string s, int hossz, int hatv)
{
	if (hossz == -1) return 0;
	else
	{
		int ossz = 0;
		int szorzo = pow(16, hatv);
	
		if (s[hossz] >= '0' && s[hossz] <= '9')
		{
			ossz = int(s[hossz]) - 48;
		}

		else if (s[hossz] >= 'A' && s[hossz] <= 'F')
		{
			ossz = int(s[hossz]) - 65 + 10;
		}

		return konv(s, hossz - 1, hatv + 1) + ossz * szorzo;

	}
}



int main()
{
	string n;
	beolvas(n);
	int hossz = n.length() - 1;
	int hatv = 0;
	cout << konv(n,hossz,hatv) << endl;
	system("PAUSE");
	return 0;

}