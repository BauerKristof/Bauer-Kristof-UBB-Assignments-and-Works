/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>

using namespace std;

class komp 
{
  protected:
	int valos;
	int imaginarius;

 public:
	komp();
	komp(int, int);
	int teritValos() const;
	int teritImaginarius() const;
	virtual komp operator *(const komp& r);
	komp& operator *=(const komp& r);
	void kiir();
};

class kompkiir : public komp 
{
    public:
	kompkiir(int valosSz, int imaginariusSz) :komp(valosSz, imaginariusSz) {};
	komp operator *(const komp& );
};

komp::komp()
{
	valos = 0;
	imaginarius = 0;
}
komp::komp(int valosSzam, int imaginariusSzam)
{
	valos = valosSzam;
	imaginarius = imaginariusSzam;
}

int komp::teritValos() const 
{
	return valos;
}
int komp::teritImaginarius() const 
{
	return imaginarius;
}

komp komp::operator *(const komp& sz) 
{
	int valosSzorzat = valos * sz.valos - imaginarius * sz.imaginarius;
	int imaginariusSzorzat = valos * sz.imaginarius + imaginarius * sz.valos;
	komp x(valosSzorzat, imaginariusSzorzat);
	return x;
}
komp& komp::operator *=(const komp& sz) 
{
	*this =(*this)*sz;
	return *this;
}

void komp::kiir() 
{
	cout << valos;
	if (imaginarius > 0)
	{
		cout << "+" << imaginarius << "i" << endl;
	}
	else if (imaginarius < 0)
	{
		cout << "-" << imaginarius << "i" << endl;
	}
}

komp kompkiir::operator *(const komp& sz) 
{
	int valosSzorzat = valos * sz.teritValos() - imaginarius * sz.teritImaginarius();
	int imaginariusSzorzat = valos * sz.teritImaginarius() + imaginarius * sz.teritValos();

	cout << '(' << valos;
	if (imaginarius > 0)
	{
		cout << "+" << imaginarius << "i)*";
	}
	else
	{
		cout << "-" << imaginarius << "i)*";
	}
	
	cout << '(' << sz.teritValos();
	if (sz.teritImaginarius() > 0)
	{
		cout << "+" << sz.teritImaginarius() << "i)= ";
	}
	else
	{
		cout << "-" << sz.teritImaginarius() << "i)=";
	}
	komp x(valosSzorzat, imaginariusSzorzat);
	x.kiir();
	return x;
}

int main()
{
		komp p(1, 2), q(3, 3), r;

		r = p *= q;

		p.kiir();

		r.kiir();

		kompkiir p1(1, 2), q1(3, 3);

		komp r1, r2;

		r1 = p1 * q1;


		r2 = p1 *= q1;

		p1.kiir();

		r1.kiir();

		r2.kiir();
	system("pause");
	return 0;
}