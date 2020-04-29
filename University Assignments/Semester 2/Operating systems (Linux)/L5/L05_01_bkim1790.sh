#!/bin/bash

#Nev: Bauer Kristof
#Azonosito: bkim1790
#Csoport: 511
#Az első paraméterként megadott állományból törölje ki a paraméterként megadott szavak összes előfordulását.

if [ $# -le 1 ]
then echo Hasznalat: $0 Allomanynev Szavak
 exit 1
fi

ALLOMANY=$1
shift

for i in $*
do
	 sed -i 's/'$i'//g' $ALLOMANY


done
