/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely kiszámítja az Ackermann-függvény értékét adott m és n értékekre:


*/


#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int &m, int &n)
{
	ifstream file;
	file.open("bkim1790_L5_5.txt");
	if (file.is_open())
	{
		file >> m >> n;
	}

}


int ack(int m, int n)
{
	if (m == 0) return n + 1;
	else if (n == 0) return ack(m - 1, 1);
	else ack(m - 1, ack(m,n-1));
}


int main()
{
	int m, n;
	beolvas(m, n);
	cout << ack(m, n) << endl;
	system("PAUSE");
	return 0;

}