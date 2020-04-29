//Bauer Kristof
//bkim1790
//511
//F4 - paratlan

#include <iostream>
#include <fstream>
#include <functional>
#include <string>

using namespace std;

ifstream file;
ofstream file2;

struct node
{
	string info;
	node *next;
	int db = 1;
};

class lista
{
	int egyedi = 0;
	node* first;

public:
	lista();
	~lista();
	void beszur(string);
	bool keres(string);
	int egyediLat();
	void kiir_rendszeres(int k);
};

int lista::egyediLat()
{
	node* r = first;
	int darab = 0;
	while (r != NULL)
	{
		if (r->db == 1)
		{
			darab++;
		}
		r = r->next;
	}
	return darab;
}
void lista::kiir_rendszeres(int k)
{
	node* r = first;
	while (r != NULL)
	{
		if (r->db >= k)
		{
			file2 << "IP Cim= " << r->info << " Hanyszor=" << r->db;
			file2 << endl;
		}
		r = r->next;
	}
}

lista::lista()
{
	first = NULL;
}

lista::~lista()
{
	while (first != NULL)
	{
		node* r = first;
		first = first->next;
		delete r;
	}
}

void lista::beszur(string elem)
{
	if (keres(elem) == false) //ha egyedi elem
	{
		node* uj = new node;
		uj->info = elem;
		uj->next = first;

		first = uj;
		egyedi++;
	}
	else
	{
		node* r = first;
		while (r != NULL && r->info != elem)
		{
			r = r->next;
		}
		r->db++;
	}
}

bool lista::keres(string elem)
{
	node* r = first;
	while (r != NULL && r->info != elem)
	{
		r = r->next;
	}

	if (r == NULL) return false;
	else return true;
}

class tabla
{
	int dim;
	int k;
	lista* H;

	hash<string> hash_f;
	int hash_ertek(string);
public:
	tabla(int, int);
	~tabla();
	void beszur(string);
	bool keres(string);
	int egyediLatogatok();
	void kiirRendszeres(int k);

};

tabla::tabla(int dimenzio, int K)
{
	dim = dimenzio;
	k = K;
	H = new lista[dimenzio];
}

tabla::~tabla()
{
	delete[] H;
}

int tabla::hash_ertek(string elem)
{
	return hash_f(elem) % dim;
}

void tabla::beszur(string elem)
{
	int index = hash_ertek(elem);
	H[index].beszur(elem);
}

bool tabla::keres(string elem)
{
	int index = hash_ertek(elem);
	return H[index].keres(elem) != NULL;
}


void tabla::kiirRendszeres(int k)
{
	file2 << "A rendszeres felhasznalok";
	file2 << endl;
	for (int i = 0; i < dim; i++)
	{
		H[i].kiir_rendszeres(k);
	}
}

int tabla::egyediLatogatok()
{
	int ossz = 0;
	for (int i = 0; i < dim; i++)
	{
		ossz += H[i].egyediLat();
	}

	return ossz;
}

int main()
{
	file.open("cimek.txt");
	file2.open("output.txt");
	if (file.is_open())
	{
		int n, k;
		string elem;
		file >> n >> k;

		tabla teszt(n, k);
		for (int i = 0; i <= n; i++)
		{
			file >> elem;
			teszt.beszur(elem);
		}
		file2 << "Egyedi latogatok szama= " << teszt.egyediLatogatok() << endl;
		teszt.kiirRendszeres(k);
	}

	file.close();
	file2.close();
	system("pause");
	return 0;
}