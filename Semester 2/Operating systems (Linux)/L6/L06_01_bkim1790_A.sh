#!/bin/bash

#Nev:Bauer Kristof
#Csoport:511
#Felhasznalo:bkim1790
#Feladat:A) A parancssorban adott egy szó, egy szám és több file neve. Írassuk ki az összes állományból azokat a sorokat, amelyekben szerepel a megadott szó, és legalább n szót tartalmaznak. Az awk script végén írjuk ki, hogy a megadott állományokban összesen hány ilyen sort találtunk.

if [ $# -lt 3 ]
then echo "Hasznalat $0 szo szam fileok"
exit 1
fi

SZO=$1
shift
SZAM=$1
shift

awk -v szo="$SZO" -v n="$SZAM" '
BEGIN {sorszam=0;}
{
   if (($0 ~ szo) && (NF>=n)) 
   {
 	print $0;
	sorszam++;
   }
}
 END { printf "\nA megadott szot %d sor tartalmazta\n",sorszam;}

' $*
