/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include <fstream>

using namespace std;

int keresmin(int tomb[100], int h)
{
	bool lat[100] = { false };

	for (int i = 1; i <h;i++)
	{
		if (tomb[i] !=0)
		{
			lat[tomb[i]] = true;
		}
	}

	for (int i = 1; i < 100; i++)
	{
		if (lat[i] == false)
		{
			return i;
		}
	}
}


int main()
{

	ifstream file;
	file.open("graf.txt");

	if (file.is_open())
	{
		int kod[100];
		int seged[100];
		int hossz;

		file >> hossz;
		hossz += 1;
		kod[0] = 0;

		for (int i = 1; i < hossz; i++)
		{
			file >> kod[i];
		}

		for (int i = 0; i <= hossz; i++)
		{
			seged[i] = kod[i];
		}

		for (int i = 1; i < hossz; i++)
		{
			seged[i] = keresmin(seged, hossz);
		}

		for (int i = 1; i < hossz; i++)
		{
			cout << "A " << seged[i] << " csucs ossze van kotve a " << kod[i] << " csuccsal" << endl;
		}
	}

	system("pause");
	return 0;
}