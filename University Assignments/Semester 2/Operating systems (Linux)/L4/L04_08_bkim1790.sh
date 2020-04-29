#!/bin/bash
#Nev:Bauer Kristof
#Azonosito: bkim1790
#Csoport: 511
#L04
#8-as feladat
#A parancssorban megadott felhasználókról írassa ki, hogy dolgoztak-e egy (első paraméterként) megadott napon vagy nem.


if [ $# -le 1 ]
then echo Hasznalat: $0 'Nap(szammal)' Felhasznalok
 exit 1
fi

NAP=$1
shift

for i
do

        for j in $(last | grep $i |tr -s ' ' | cut -d' ' -f6)
        do
                if [ "$NAP" = "$j" ]
                then echo "$i dolgozott a megadott napon"
                break;
                fi
        done
done

