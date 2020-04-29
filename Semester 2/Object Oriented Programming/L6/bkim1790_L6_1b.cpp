/*
Bauer Kristof
Csoport:511
*/
#include <iostream>

using namespace std;

class Idopont
{
	int ora, perc, masodperc;
	
public:
	Idopont(int h, int m, int s);
	void kiir();
	Idopont operator ++(int);
	Idopont &operator ++();

};

Idopont& Idopont::operator ++() 
{
	masodperc++;
	if (masodperc == 60) 
	{
		masodperc = 0;
		perc++;
		if (perc == 60) 
		{
			perc = 0;
			ora++;
			if (ora == 24) 
			{
				ora = 0;
			}
		}
	}
	return *this;
}

Idopont Idopont::operator ++(int)
{
	int H = ora;
	int M = perc;
	int S = masodperc;
	masodperc++;

	if (masodperc == 60)
	{
		masodperc = 0;
		perc++;
		if (perc == 60)
		{
			perc = 0;
			ora++;
			if (ora == 24)
			{
				ora = 0;
			}
		}
	}
	return Idopont(H, M, S);
}

void Idopont::kiir()
{
	if (ora < 10)
	{
		cout << 0 << ora;
	}
	else 
	{
		cout << ora;
	}
	cout << ":";
	
	if (perc < 10) 
	{
		cout << 0 << perc;
	}
	else 
	{
		cout << perc;
	}
	cout << ":";
	if (masodperc < 10) 
	{
		cout << 0 << masodperc;
	}
	else 
	{
		cout << masodperc;
	}
	cout << endl;
}

Idopont::Idopont(int h, int m, int s)
{

	if (h < 0 || h>24)
	{
		throw "Hibas ora";
	}
   if (m < 0 || m>60)
	{
	   throw "Hibas perc";
	}
     if (s < 0 || s>60)
	{
		 throw "Hibas masodperc";
	}

	 ora = h;
	 perc = m;
	 masodperc = s;
}

int main()
{
	try
	{
		Idopont ido(16, 23, 59);
		(++ido).kiir();
		ido.kiir();
		//ido.kiir();
	}
	catch (const char* uzenet)
	{
		cout << uzenet << endl;
	}

	system("pause");
	return 0;
}