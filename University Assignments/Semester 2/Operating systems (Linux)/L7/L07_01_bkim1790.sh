#!/bin/bash

#Nev:Bauer Kristof
#Csoport:511
#Felhasznalo:bkim1790
#Feladat 1 Adott egy "keszlet" nevű állomány, amely egy üzlet árukészletét tartalmazza (termék - ár - darabszám formátumban) ...

if [ $# -gt 1 ]
then echo "Hasznalat: $0 Periodus(mp)"
exit 1
fi

PERIODUS=60; #masodpercek szama
if [ $# -eq 1 ]
then 
	if [[ ! $1 =~ ^[0-9]+$ ]]
    	then
        echo "HIBA: A periodus csak szam lehet"
	exit 1
	fi

	PERIODUS=$1
fi

while :; do
 cat uj_aru>>keszlet
 awk '{print $2*$3, $0}' keszlet | sort -rn | cut -d' ' -f 2-4
 printf "\n";
 mv uj_aru uj_aru"$(date +"%Y-%m-%d-%H-%M-%S")"
 sleep $PERIODUS
done

