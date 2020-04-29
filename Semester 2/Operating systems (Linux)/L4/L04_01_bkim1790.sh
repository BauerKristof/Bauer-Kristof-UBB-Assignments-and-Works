#!/bin/bash
#Nev:Bauer Kristof
#Azonosito: bkim1790
#Csoport: 511
#L04
#1-es feladat
#Írassa ki a paraméterként megadott katalógusban és alaktalógusaiban szereplő szöveges file-ok "."-al vagy számjeggyel kezdődő sorait.

if [ $# != 1 ]
then echo Hasznalat: $0 katalogus
 exit 1
fi

if [ ! -d "$1" ]
then echo "A parameter nem egy katalogus, probald ujra"
exit 1
fi

#Grep rekurziv funkciojat hasznalva rakerestem minden olyan filera ami illeszkedik a mintara, szoveges file(nem binary file), es elmentettem az utvonalat
for i in `grep -RIEls '^[0-9].*|^[.].*' "$1"`
do
        if [ "$(file $i)" = "$i: ASCII text" ]  #ezutan megneztem, hogy az adott file kimondottan ASCII file-e
        then

                grep -HEwn '^[0-9].*|^[.].*' $i #Ha igen kiirom a fileon belul azokat asorokat amik illeszkednek a mintara

        fi
done
