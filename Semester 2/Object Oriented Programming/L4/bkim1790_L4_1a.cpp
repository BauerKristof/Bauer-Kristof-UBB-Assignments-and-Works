/*
Bauer Kristof
Csoport: 511
*/

#include <iostream>
#include <exception>

using namespace std;


class Tele {};
class Ures {};

class Lista
{
	
	int *a;
	int tail = -1;
	int h;

public:
	Lista(int h);
	int get_hossz() const;
	void push(int);
	int pop();
	void printOut() const;
};

Lista::Lista(int hossz)
{
	h = hossz;
	a = new int[h];
}

int Lista::get_hossz() const { return h; }

void Lista::push(int szam)
{
	tail++;
	if (tail > h)
	{
		throw(Tele());
	}
	a[tail] = szam;
}

int Lista::pop()
{
	tail--;
	if (tail < 0)
	{
		throw(Ures());
	}

}

void Lista::printOut() const
{
	for (int i = 0; i < tail; i++)
	{
		cout << a[i]<<" ";
	}
}


int main()
{
	Lista l(2);
	cout << l.get_hossz() << endl;
	
	
	try 
	{
		l.pop();
		l.pop();
	}
	catch (Ures) 
	{
		cout << "Ures" << endl;
	}

	l.push(10);
	l.push(2);

	try 
	{
		l.push(1);
		l.push(10);
		l.push(20);
	}
	catch (Tele) 
	{
		cout << "Betelt" << endl;
	}

	system("pause");
	return 0;
}