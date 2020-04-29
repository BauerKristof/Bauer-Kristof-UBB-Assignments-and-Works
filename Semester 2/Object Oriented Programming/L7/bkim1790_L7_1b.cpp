/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>

using namespace std;

class Ido
{
	int ora=0, perc=0, masodperc=0;
public:
	Ido(int s);
	Ido(int, int, int);
	Ido &operator +=(const Ido &i);
	Ido &operator -=(const Ido &i);
	void kiir();
};

Ido& Ido::operator +=(const Ido &i)
{
	masodperc += i.masodperc;
	perc += i.perc;
	ora += i.ora;
	
	int maradekMasodperc;

	int masodPercOraban = 60 * 60;
	int masodpercPercben = 60;

	ora = (masodperc / masodPercOraban);
	maradekMasodperc = masodperc - (ora * masodPercOraban);
	perc = maradekMasodperc / masodpercPercben;
	maradekMasodperc = maradekMasodperc - (perc*masodpercPercben);
	masodperc = maradekMasodperc;

	return *this;
}

Ido& Ido::operator -=(const Ido &i)
{
	masodperc -= i.masodperc;
	perc -= i.perc;
	ora -= i.ora;

	int maradekMasodperc;

	int masodPercOraban = 60 * 60;
	int masodpercPercben = 60;

	ora = (masodperc / masodPercOraban);
	maradekMasodperc = masodperc - (ora * masodPercOraban);
	perc = maradekMasodperc / masodpercPercben;
	maradekMasodperc = maradekMasodperc - (perc*masodpercPercben);
	masodperc = maradekMasodperc;

	return *this;
}
Ido::Ido(int o, int p, int mp)
{
	ora = ora;
	perc = perc;
	masodperc = mp;
}

Ido::Ido(int s)
{
		int maradekMasodperc;

		int masodPercOraban = 60 * 60;
		int masodpercPercben = 60;
		
		ora = (s / masodPercOraban);
		maradekMasodperc = s - (ora * masodPercOraban);
		perc = maradekMasodperc / masodpercPercben;
		maradekMasodperc = maradekMasodperc - (perc*masodpercPercben);
		masodperc = maradekMasodperc;

}

void Ido::kiir()
{
	cout << ora << ":" << perc << ":"<<masodperc << endl;
}

int main()
{
	//Ido a(0, 1, 59);
	//a.kiir();
	Ido b(9605);
	b.kiir();    // 2 óra 40 perc 5 másodperc;
	system("pause");
	return 0;
}