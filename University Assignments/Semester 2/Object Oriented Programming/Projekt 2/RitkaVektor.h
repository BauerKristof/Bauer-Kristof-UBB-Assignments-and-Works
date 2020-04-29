/*Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790*/

#pragma once
#include "Vektor.h"

template < class T >
struct nonZero
{
	T elem;
	int index;
};


template<class T>
class RitkaVektor
{
public:
	operator Vektor<T>();
	RitkaVektor() {}
	RitkaVektor(int dim);
	RitkaVektor(T *t, int dim);
	RitkaVektor(const RitkaVektor&);
	~RitkaVektor();

	RitkaVektor operator+(const RitkaVektor&);
	RitkaVektor operator-(const RitkaVektor&);
	double operator*(const RitkaVektor&);
	double operator~();
	double operator%(const RitkaVektor&);
	T      operator[](int) const;

private:
	nonZero <T> * vektor;
	int nZeroDim;
	int dim;
};

template <class T>
RitkaVektor<T>::operator Vektor<T>()
{
	T* eredmeny = new T[dim];
	for (int i = 0; i < dim; i++)
	{
		eredmeny[i] = (*this)[i];
	}

	Vektor<T> x(eredmeny, dim);
	delete[] eredmeny;
	return x;
}

template <class T>
RitkaVektor<T>::RitkaVektor(int dim)
{
	(*this).dim = dim;
	nZeroDim = 1;
	vektor = new nonZero<T>[1];
	vektor[0].elem = 1;
	vektor[0].index = 0;
}

template <class T>
RitkaVektor<T>::RitkaVektor(T *t, int dim)
{
	this->dim = dim;
	nZeroDim = 0;
	for (int i = 0; i < dim; i++)
	{
		if (t[i] != 0)
		{
			nZeroDim++;
		}
	}

	vektor = new nonZero<T>[nZeroDim];
	int n = 0;

	for (int i = 0; i < dim; i++)
	{
		if (t[i] != 0)
		{
			vektor[n].index = i;
			vektor[n].elem = t[i];
			n++;
		}
	}
}

template <class T>
RitkaVektor<T>::RitkaVektor(const RitkaVektor& v)
{
	dim = v.dim;
	nZeroDim = v.nZeroDim;
	vektor = new nonZero<T>[nZeroDim];

	for (int i = 0; i < nZeroDim; i++)
	{
		vektor[i].elem = v.vektor[i].elem;
		vektor[i].index = v.vektor[i].index;
	}
}

template <class T>
RitkaVektor<T>::~RitkaVektor()
{
	delete[] vektor;
}

template <class T>
RitkaVektor<T> RitkaVektor<T>:: operator+(const RitkaVektor &v)
{
	if (dim != v.dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	T* osszeg = new T[dim];

	for (int i = 0; i < dim; i++)
	{
		osszeg[i] = 0;
	}

	for (int i = 0; i < nZeroDim; i++)
	{
		osszeg[vektor[i].index] += vektor[i].elem;
	}

	for (int i = 0; i < v.nZeroDim; i++)
	{
		osszeg[v.vektor[i].index] += v.vektor[i].elem;
	}

	RitkaVektor x(osszeg, dim);
	delete[] osszeg;
	return x;
}

template <class T>
RitkaVektor<T> RitkaVektor<T>:: operator-(const RitkaVektor &v)
{
	if (dim != v.dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	T* kulonbseg = new T[dim];

	for (int i = 0; i < nZeroDim; i++)
	{
		kulonbseg[vektor[i].index] = vektor[i].elem;
	}

	for (int i = 0; i < v.nZeroDim; i++)
	{
		kulonbseg[v.vektor[i].index] -= v.vektor[i].elem;
	}

	RitkaVektor x(kulonbseg, dim);
	delete[] kulonbseg;
	return x;
}

template <class T>
double RitkaVektor<T>::operator*(const RitkaVektor& v)
{
	if (dim != v.dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	double skalar = 0.0;

	for (int i = 0; i < nZeroDim; i++)
	{
		for (int j = 0; j < v.nZeroDim; j++)
		{
			if (vektor[i].index == v.vektor[j].index)
			{
				skalar += vektor[i].elem*v.vektor[j].elem;
			}
		}
	}

	return skalar;
}

template<class T>
double RitkaVektor<T>::operator~()
{
	double norma = 0.0;

	for (int i = 0; i < nZeroDim; i++)
	{
		norma += vektor[i].elem * vektor[i].elem;
	}

	norma = sqrt(norma);
	return norma;
}

template<class T>
double RitkaVektor<T>::operator%(const RitkaVektor& v)
{
	if (dim != v.dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	double tavolsag = 0.0;

	for (int i = 0; i < nZeroDim; i++)
	{
		for (int j = 0; j < v.nZeroDim; j++)
		{
			if (vektor[i].index == v.vektor[j].index)
			{
				tavolsag += (vektor[i].elem - v.vektor[j].elem) * (vektor[i].elem - v.vektor[j].elem);
			}
		}
	}
	return sqrt(tavolsag);
}

template<class T>
T RitkaVektor<T>::operator[](int poz) const
{
	if ((poz < 0) || (poz >= dim))
	{
		throw "HIBA: Nincs ilyen elem";
	}

	int i = 0;

	while ((vektor[i].index != poz) && (i < nZeroDim))
	{
		i++;
	}

	if (i != nZeroDim)
	{
		return vektor[i].elem;
	}
	else
	{
		return 0;
	}
}