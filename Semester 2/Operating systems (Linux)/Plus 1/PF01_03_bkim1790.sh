#!/bin/bash

if [ $# -eq 0 ]
then
echo "Hasznalat: $0 parameterek"
exit 1
fi


for i in $* ;do 
 if [ -d $i ] 
 then echo "$i katalogusban `ls|wc -l` bejegyzes talalhato, merete: `du -hs $i|cut -f1`"
 elif [ -f $i ] 
 then echo "$i - `wc -l $i | cut -d" " -f1`" >> allomanyok.txt 
 else 
 echo "$i hibas parameter" 
 fi 
 done 
 
 sort -k3nr -t" " -o allomanyok.txt allomanyok.txt
