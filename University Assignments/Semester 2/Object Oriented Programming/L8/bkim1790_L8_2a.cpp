/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
using namespace std;
class Tomeg_d;
class Tomeg_g 
{
	int kg;
	int dkg;
	int g;
	double maradek;

public:
	Tomeg_g(int , int , int );
	Tomeg_g(const Tomeg_d& );
	int atGramm() const;
	operator Tomeg_d();
	void kiir();
};


class Tomeg_d 
{
	int font;
	int uncia;
	int dram;
	double maradek;
public:
	Tomeg_d(int , int , int );
	Tomeg_d(const  Tomeg_g& );
	int atDram() const;
	operator Tomeg_g();
	void kiir();
};

Tomeg_g::Tomeg_g(int kilo, int deka, int gramm) 
{
	kg = kilo;
	dkg = deka;
	g = gramm;
	maradek = 0;

	if (g >= 10) 
	{
		dkg += g / 10;
		g %= 10;
	}

	if (dkg >= 100) 
	{
		kg += dkg / 100;
		dkg %= 100;
	}
}

Tomeg_g::Tomeg_g(const Tomeg_d& szam) 
{
	maradek = szam.atDram() * 0.564382;
	g = trunc(maradek);
	maradek -= g;

	dkg = 0;
	kg = 0;
	
	if (g > 9) 
	{
		dkg += g / 10;
		g %= 10;
	}

	if (dkg >= 100) {
		kg += dkg / 100;
		dkg %= 100;
	}
}

int Tomeg_g::atGramm() const 
{
	int alakit = g;
	alakit += 100 * dkg;
	alakit += 1000 * kg;
	return alakit;
}

Tomeg_g::operator Tomeg_d() 
{
	return Tomeg_d(*this);
}

void Tomeg_g::kiir() 
{
	if (kg != 0)
		cout << kg << " kg ";
	if (dkg != 0)
		cout << dkg << " dkg ";
	
	if ((g + maradek) > 0)
	{
		cout << g + maradek << " g";
	}
	if (kg == 0 && dkg == 0 && (g + maradek) == 0)
	{
		cout << "0 g";
	}
	cout << endl;
}


Tomeg_d::Tomeg_d(int f, int u, int d) 
{
	font = f;
	uncia = u;
	dram = d;
	maradek = 0;

	if (dram >= 16) 
	{
		uncia += dram / 16;
		dram %= 16;
	}

	if (uncia >= 16) 
	{
		font += uncia / 16;
		uncia %= 16;
	}
}

Tomeg_d::Tomeg_d(const Tomeg_g& szam) 
{
	maradek = szam.atGramm() * 1.77;
	dram = trunc(maradek);
	maradek -= dram;
	uncia = 0;
	font = 0;
	
	if (dram >= 16) 
	{
		uncia += dram / 16;
		dram %= 16;
	}

	if (uncia >= 16) 
	{
		font += uncia / 16;
		uncia %= 16;
	}
}

int Tomeg_d::atDram() const 
{
	int alakit = dram;
	alakit += 16 * uncia;
	alakit += 256 * font;
	return alakit;
}

Tomeg_d::operator Tomeg_g() 
{
	return Tomeg_g(*this);
}

void Tomeg_d::kiir() 
{
	if (font > 0)
		cout << font << " font ";
	if (uncia > 0)
		cout << uncia << " uncia ";
	
	if ((dram + maradek) > 0)
	{
		cout << dram + maradek << " dram";
	}
	
	if (font == 0 && uncia == 0 && (dram + maradek) == 0)
	{
		cout << "0 dram";
	}
	cout << endl;
}

int main()
{
	Tomeg_g szam1(0, 0, 1);
	cout << "Gramm= ";
	szam1.kiir();
	cout << "Gramm->Dram= ";
	((Tomeg_d)szam1).kiir();
	
	Tomeg_d szam2(0, 0, 1);
	cout << "Dram= ";
	szam2.kiir();
	Tomeg_g atAlakit(szam2);
	cout << "Dram->Gramm= ";
	atAlakit.kiir();
	system("pause");
	return 0;
}
