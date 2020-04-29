#!/bin/bash

#Nev:Bauer Kristof
#Azonosito:bkim1790
#Csoport:511
#Feladat:L11
#Feladatszam:1
#Feladat szovege:A kliens shell parancsok végrehajtását kéri a szervertől. A szerver nyilvántart egy "engedélyezett utasításokat" tartalmazó listát


if grep -Fxq "$1" input.dat #szerepel-e a fileba
then
         if which "$1" >/dev/null #van-e eleresi utvonala
         then
            UTVONAL=`which "$1"` #LEHET IDE WHICH KELL!!!!
              if [ -x "$UTVONAL" ] #ha van futthathato-e a parancs
              then
                 HANYSZOR=0

                 for i in `echo "$PATH" | awk -F: '{for(i=1;i<=NF;i++) { printf $i; printf("\n");} }'` #ha igen levalasztja az utvonalat
                 do
			for j in `find "$i" -name "$1"` #megnezi hogy megtalalja-e benne az allomanyunkat
                        do
                          if [ -x "$j" ] #ha talalt meg ilyen allomanyt es futtathato
                           then
                           let HANYSZOR+=1
                         fi
                        done
                 done

                if [ $HANYSZOR -gt 1 ]
                then
                echo FIGYELEM: Az eleresi utvonalak kozott a parancs $HANYSZOR-szer megtalalhato
                fi

                exec "$1" #ha minden jo vegrehajtuk a parancsot

               else
               echo "nem vegrehajthato parancs"
               fi
          else
          echo "ismeretlen parancs";
          exit 0;
         fi
else
    echo "nem engedelyezett parancs"
    exit 0
fi

