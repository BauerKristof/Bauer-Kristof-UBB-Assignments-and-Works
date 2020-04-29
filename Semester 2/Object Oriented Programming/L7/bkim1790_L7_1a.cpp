/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>

using namespace std;

template <class T>
class Verem
{
	
	template <class T>
	struct Elem 
	{
		Elem *kov;
		T info;
	};

	Elem<T> *teteje;
	int max_meret;
	int aktualis_meret;

	public:
		Verem(int _max_meret);
		~Verem();
		void betesz(T adat);
		void kivesz();
		void kiir();
		T& operator [](int i);
		void operator ()(T(*fg)(T));



};

template <class T>
void Verem<T>::operator ()(T(*fg)(T)) 
{
	Elem<T> *tmp=teteje;

	while (tmp != NULL)
	{
		tmp->info = fg(tmp->info);
		tmp=tmp->kov;
	}

}

template <class T>
T& Verem<T>::operator [](int i)
{
	
	if (i > aktualis_meret || i<0) 
	{
		throw "HIBA:Nincsi ilyen index";
	}
	else 
	{
		Elem<T> *seged;
		seged = teteje;
		int j = 0;

		while (j < i) 
		{
			seged = seged->kov;
			j++;
		}
		return seged->info;
	}
}

template<class T>
void Verem<T>::kiir() 
{
	Elem<T> *seged;
	seged = teteje;

	while (seged != NULL) 
	{
		cout << seged->info << " ";
		seged = seged->kov;
	}
	cout << endl;
}

template <class T>
void Verem<T>::kivesz() 
{
	Elem<T> *seged;
	seged = new Elem<T>;

	if (teteje==NULL)
	{
		throw "HIBA: Alulcsordulas";
	}
	else 
	{
		seged = teteje;
		teteje = teteje->kov;
		delete seged;
		aktualis_meret--;

	}
}


template <class T>
void Verem<T>::betesz(T adat) 
{
	if (aktualis_meret < max_meret) 
	{
		Elem<T>* uj;

		uj = new Elem<T>;
		uj->info = adat;
		uj->kov = teteje; 
		teteje = uj;
		aktualis_meret++;
	}
	else 
	{
		throw "HIBA:Tulcsordulas";
	}
}

template <class T>
Verem<T>::Verem(int _max_meret)
{
	max_meret = _max_meret;
	teteje = NULL;
}

template <class T>
Verem<T>::~Verem()
{
	for (int i = aktualis_meret; i > 0; i--)
	{
		kivesz();
	}
}

template <class T>
T felez(T szam)
{
	return szam / 2;
}

int main()
{
	try
	{
		Verem <int> elem(3);
		elem.betesz(4);
		elem.betesz(5);
		elem.kiir();
		elem.kivesz();
		elem.kiir();
		cout << elem[0] << endl;
		elem.betesz(6);
		elem(felez);
		elem.kiir();
	}
	
	catch (const char* uzenet)
	{
		cout << uzenet << endl;
	}


	system("pause");
	return 0;
}