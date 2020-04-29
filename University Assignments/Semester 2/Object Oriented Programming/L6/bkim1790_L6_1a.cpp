/*
Bauer Kristof
511 csoport
*/

#include <iostream>

using namespace std;

class Rac
{
	int sz, n;
	int lnko(int a, int b);

public:
	Rac(int, int);
	Rac operator *(const Rac);
	Rac& operator*=(const Rac &m);
	Rac operator +(const Rac);
	Rac& operator+=(const Rac &m);
	void kiir();
	
};

Rac& Rac:: operator+=(const Rac &m)
{
	*this = *this + m;
	return *this;
}
int Rac::lnko(int szam1, int szam2)
{
	int a = szam1;
	int b = szam2;
	while (a != b)
	{
		if (a > b) { a -= b; }
		else { b -= a; }
	}
	return a;
}

Rac Rac::operator +(const Rac szam) 
{
	Rac b(sz,n);
	int e, f;
	e = b.sz*szam.n + b.n*szam.sz;
	f = b.n*szam.n;

		b.sz = e;
	    b.n = f;

		int l= lnko(e,f);
	b.sz /= l;
	b.n /= l;
	return b;

}

Rac::Rac(int szamlalo, int nevezo)
{
	sz = szamlalo;
	n = nevezo;
}

Rac Rac::operator *(const Rac szam) 
{
	int sz1 = sz * szam.sz;
	int sz2 = n * szam.n;
	int k = lnko(sz1, sz2);
	sz1 /= k;
	sz2 /= k;
	return Rac(sz1, sz2);
}

Rac& Rac::operator *=(const Rac &m) 
{
	sz *= m.sz;
	n *= m.n;
	int k = lnko(sz, n);
	sz /= k;
	n /= k;
	return *this;
}

void Rac::kiir()
{
	cout << sz << "/" << n << endl << endl;
}

int main()
{
	Rac tort1(5, 2);
	Rac tort2(1, 4);

	tort1.kiir();
	tort2.kiir();
	(tort1*tort2).kiir();
	tort1.kiir();
	tort1 *= tort2;
	tort1.kiir();
	tort1 += tort2;
	tort1.kiir();
	system("pause");
	return 0;
}