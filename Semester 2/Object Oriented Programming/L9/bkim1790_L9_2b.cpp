/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>

using namespace std;

class Alakzat
{
	public:
		virtual double kerulet() = 0;
		virtual double terulet() = 0;
		virtual void nagyit(double s) = 0;
};

class Kor :public Alakzat
{
	double r;

    public:
	Kor()
	{
		r = 0;
	}

	Kor(double sugar)
	{
		r = sugar;
	}

	double kerulet()
	{
		return 2 * 3.1415*r;
	}

	double terulet()
	{
		return 3.1415*(r*r);
	}

    void nagyit(double s)
	{
	 r*= s;
	}

};

class Teglalap : public Alakzat
{
   protected:
	double H, SZ;

   public:
	Teglalap()
	{
		H = 0;
		SZ = 0;
	}
	
	Teglalap(double hossz, double szel)
	{
		H = hossz;
		SZ = szel;
	}

	double kerulet()
	{
		return 2 * H + 2 * SZ;
	}

	double terulet()
	{
		return H * SZ;
	}

	void nagyit(double s)
	{
		H *= s;
		SZ *= s;
	}
};

class Negyzet : public Teglalap
{
    public:
	Negyzet(double hossz, double szel) : Teglalap(hossz, szel) 
	{
		if (hossz != szel)
		{
			throw "HIBA:Nem negyzet";
		}
	};
	
};

int main()
{
	Alakzat *a[] = { new Kor(3), new Teglalap, new Negyzet(2,2) };

	cout << a[0]->kerulet() << ", " << a[0]->terulet() << endl;

	cout << a[1]->kerulet() << ", " << a[1]->terulet() << endl;

	cout << a[2]->kerulet() << ", " << a[2]->terulet() << endl;

	system("pause");
	return 0;
}