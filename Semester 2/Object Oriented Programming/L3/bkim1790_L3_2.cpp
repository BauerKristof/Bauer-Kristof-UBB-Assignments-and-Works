/*
Nev: Bauer Kristof
Csoport: 511
*/

#include <iostream>
#include <cmath>

using namespace std;

class Pont
{
	double x, y;

	public:
	Pont();
	Pont(double X, double Y);
	double get_x();
	double get_y();
	void kiir();
};

Pont::Pont()
{
	x = 0;
	y = 0;
}

Pont::Pont(double X, double Y)
{
	x = X;
	y = Y;
}

double Pont::get_x()
{
	return x;
}

double Pont::get_y()
{
	return y;
}



void Pont :: kiir()
{
	cout << "Az x koordinata: " << x << " y koordinata: " << y << endl;
}

class Vektor
{
	Pont p1, p2;

public:
	Vektor() :p1(), p2() {}
	Vektor(Pont _p1, Pont _p2);
	Pont get_kp();
	Pont get_vp();
	double eukNorm();
	double fokSzam();
};

Vektor::Vektor(Pont _p1, Pont _p2)
{
	p1 = _p1;
	p2 = _p2;
}

Pont Vektor::get_kp()
{
	return p1;
}

Pont Vektor::get_vp()
{
	return p2;
}

double Vektor::fokSzam()
{
	double x2 = p2.get_x();
	double x1 = p1.get_x();
	double y2 = p2.get_y();
	double y1 = p1.get_y();

	y2 -= y1;
	x2 -= x1;
	double szog=atan(y2 / x2);
	return szog * (180.0 / 3.141592653589793238463);

}

double Vektor::eukNorm()
{
	double x2 = p2.get_x();
	double x1 = p1.get_x();
	double y2 = p2.get_y();
	double y1 = p1.get_y();
	return sqrt( pow((x2 - x1), 2) + pow((y2 - y1), 2));

}


int main()
{
	Pont p1(1, 1);
	Pont p2(2, 2);
	Pont p3,p4;

	Vektor v1;
	p3 = v1.get_kp();
	p4 = v1.get_vp();
	p3.kiir();
	p4.kiir();
	Vektor v2(p1,p2);

	p3 = v2.get_kp();
	p4 = v2.get_vp();
	p3.kiir();
	p4.kiir();

	cout << v2.eukNorm() << endl;
	cout << v2.fokSzam() << endl;

	system("pause");
	return 0;
}