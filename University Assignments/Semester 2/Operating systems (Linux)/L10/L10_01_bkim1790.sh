#!/bin/bash

#Azonosito:bkim1790
#Csoport:511
#Feladatcsoport:L10
#Feladat szama:01
#Szoveg:A kliens egy (hh:mm formátumú) időpontot küld a szervernek, amelyet az input.dat állományból olvas. A szerver visszaküldi az összes olyan felhasználó (felhasználó)nevét, akik éppen dolgoznak, és a mai napon a megadott időpont után jelenkeztek be. */



#last | grep "`date +%B` `date + %d`"
NAP=0
NAP=`last -n 1 | grep "still" | sed s/"  */ /g" | cut -d" " -f6` #megnezem az aktualis napot
last | head -1000 > temp #rendezem az utolso 1000 bejelentkezesek szerint
cat temp | while read line
do
 BNAP=`echo $line| cut -d" " -f6` #megkapom folyamat napjat
 if [ "$BNAP" == "$NAP" ] #ha az egyezik az aktualis napunkkal
 then
 FELHASZNALO=`echo $line| cut -d" " -f1`
 DOLGOZIK=`echo $line| cut -d" " -f8`
 if echo $DOLGOZIK | grep "still" >>/dev/null #ha meg dolgozik
 then
 IDO=`echo $line | cut -d" " -f7`
 VEGEREDMENYORA=`echo $IDO | cut -d":" -f1`
 VEGEREDMENYPERC=`echo $IDO | cut -d":" -f2`
 VEGEREDMENYORA=`expr $VEGEREDMENYORA \* 60` #lekerem a bejelentkezes idejet, atalakitom percbe es visszaterit
 TERIT=`expr $VEGEREDMENYORA + $VEGEREDMENYPERC`
 echo "$FELHASZNALO#$TERIT"
 fi
  else #ha a nap nem egyezik az aktualis napunkkal veget er a folyamat, nem olvasunk tovabb
  break
fi
done

rm temp #toroljuk a temp filet
#Megjegyzes: azert sortoltam lastot head 1000-re es listaztam csak az utolso 1000 bejeltkezest, mert 17800 bejeltkezes volt a szerveren, ami kifagyasztja a ciklust +
#nem latom ertelmet tobb mint 1000 bejelentkezest nezni, mert annyi nem fog megtortenni a szerveren egy nap alatt es csak feleslegesen fut

