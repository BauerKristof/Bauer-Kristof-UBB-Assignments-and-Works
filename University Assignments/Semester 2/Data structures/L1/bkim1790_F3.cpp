/*
Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790
FELADAT - Folyamatok ütemezése
*/


#include <iostream>
#include <fstream>

using namespace std;

ifstream file("teszt.txt");
ofstream file2("kimenet.txt");

struct ElemTipus
{
	int id;
	int vido;
};

struct VarakozasiSorTipus
{
	ElemTipus info;
	VarakozasiSorTipus* kov; 
};

class VarakozasiSor
{	
		VarakozasiSorTipus* fej;
		VarakozasiSorTipus* utolso;
    
public:
		VarakozasiSor();
		~VarakozasiSor();
		void Kiir();
		void Beszur(int ID, int VarIdo);
		double Atlag_varakozas();
		int Kivesz();
}; 

int VarakozasiSor::Kivesz()
{
	if (fej == NULL)
	{
		return -1;
	}
	else
	{
		VarakozasiSorTipus* r;
		r = fej;  
		int azonosito = r->info.id;            
		fej = fej->kov; 
		delete r; 
		return azonosito;
	}
}

VarakozasiSor::~VarakozasiSor()
{
	VarakozasiSorTipus* r;

	while (fej)
	{
		r = fej;
		fej = fej->kov;
		delete r;
	}
	utolso = NULL;
}

double VarakozasiSor::Atlag_varakozas()
{
	double atlag=0;
	int elemszam=0;

	VarakozasiSorTipus* r = fej;     
	while (r)
	{
		elemszam++;
		atlag = atlag + r->info.vido;
		r = r->kov; 
	}

	return atlag /= elemszam;

}

VarakozasiSor::VarakozasiSor()
{
	fej = NULL;
	utolso = NULL;
}

void VarakozasiSor::Kiir()
{
	cout << endl;
	cout << "A LISTA TARTALMA" << endl;
	file2 << "A LISTA TARTALMA" << endl;

	VarakozasiSorTipus* r = fej;    
	while (r)
	{
		cout << "ID:  " << r->info.id << " " << "Varakozasi ido: " << r->info.vido << endl;
		file2<< "ID:  " << r->info.id << " " << "Varakozasi ido: " << r->info.vido << endl;
		r = r->kov;
	}
	cout << endl;
}

void VarakozasiSor::Beszur(int ID, int VarIdo)
{
		VarakozasiSorTipus* p;
		p = new VarakozasiSorTipus;
		p->info.id = ID;
		p->info.vido = VarIdo;
		p->kov = NULL;
		if (fej == NULL)
		{
			fej = p;
		}
		else {
			utolso->kov = p;
		}
		utolso = p;
}

int main()
{

	if (file.is_open())
	{
		VarakozasiSor l;
		int n, ID, VIDO;
		file >> n;

		for (int i = 1; i <= n; i++)
		{
			file >> ID >> VIDO;
			l.Beszur(ID, VIDO);
		}

		l.Kiir();
		cout << "Atlag varkaozasi ido: " << l.Atlag_varakozas() << endl;
		file2 << "Atlag varkaozasi ido: " << l.Atlag_varakozas() << endl;
		for (int i = 1; i <= 5; i++) { l.Kivesz(); }

		l.Kiir();
		cout << "Atlag varkaozasi ido: " << l.Atlag_varakozas() << endl;
		file2 << "Atlag varkaozasi ido: " << l.Atlag_varakozas() << endl;
	}

	file.close();
	file2.close();

	system("pause");
	return 0;
}