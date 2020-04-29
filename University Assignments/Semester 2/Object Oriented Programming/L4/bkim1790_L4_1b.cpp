/*
Bauer Kristof
Csoport:511
*/

#include <iostream>

using namespace std;


const char* keres(const char* elso, const char* masodik)
{
	int hossz1 = 0, hossz2 = 0;
	while (elso[hossz1] != '\0')
	{
		hossz1++;
	}

	while (masodik[hossz2] != '\0')
	{
		hossz2++;
	}


	int i = 0;
	bool azonos = true;
	while ( (i < hossz1) && (azonos))
	{
		if (elso[i] == masodik[0])
		{
			int j = 0;
			int poz = i;

			while ((j < hossz2) && (masodik[j] == elso[i]))
			{
				i++;
				j++;
			}

			if (j == hossz2)
			{
				return &elso[poz];
				azonos = false;
			}

		}
		i++;
	}

	if (azonos == true)
	{
		throw "Nem talalta meg a masik stringben";
	}

}

int main()
{
	try
	{
		cout << keres("klasabcdef", "abc") << endl;
	}

	catch (const char* error) 
	{
		cout << error << endl;
	}
	system("pause");
	return 0;
}