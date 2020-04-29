/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include <string>
using namespace std;

class E
{
protected: int e;
public:
	E(string &str)
	{
		str += "E";
		e = 1;
	}
};

class F
{
protected: int f;
public:
	F(string &str)
	{
		str += "F";
		f = 1;
	}
};


class A : virtual public E
{
protected: int a;
public:
	A(string &str) :E(str)
	{
		str += "A";
		a = 1;
	}
};



class B : virtual public E
{
protected: int b;
public:
	B(string &str) :E(str)
	{
		str += "B";
		b = 1;
	}
};

class C : virtual public E
{
protected: int c;
public:
	C(string &str) :E(str)
	{
		str += "C";
		c = 1;
	}
};



class D: public F
{
protected: int d;
public:
	D(string &str):F(str)
	{
		str += "D";
		d = 1;
	}
};


class G:public F
{
protected: int g;
public:
	G(string &str):F(str)
	{
		str += "G";
		g = 1;
	}
};

class H:public F
{
protected: int h;
public:
	H(string &str):F(str)
	{
		str += "H";
		h = 1;
	}
};

class I:public F
{
protected: int i;
public:
	I(string &str):F(str)
	{
		str += "I";
		i = 1;
	}
};


class J:public A,public B,public C, public D,public G,public H, virtual public I
{
protected: int j;
public:
	J(string &str) :A(str), B(str), C(str), E(str), D(str), G(str), H(str), I(str)
	{
		str += "J";
		j = 1;
		cout << str << endl;
	}

	void kiir()
	{
		cout << "a= " << a<<endl;
		cout << "b= " << b<<endl;
		cout << "c= " << c << endl;
		cout << "d= " << d << endl;
		cout << "e= " << e << endl;
		cout << "f=" << D::f << endl;
		cout << "g= " << g << endl;
		cout << "h=" << h << endl;
		cout << "i= " << i << endl;
		cout << "j= " << j << endl;
	}
};





int main()
{
	string a;
	J szam(a);
	szam.kiir();
	system("pause");
	return 0;
}






