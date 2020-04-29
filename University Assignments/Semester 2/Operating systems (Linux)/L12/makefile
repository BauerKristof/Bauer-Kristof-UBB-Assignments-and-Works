# Bauer Kristof
# bkim1790
# L12_01
# Írjunk egy fogyasztó és egy ellátó (termelő) programot, a fogyasztó egy lerakatban szereplő árukat fogyasztja a termelő pedig a lerakatot új áruval látja el. A lerakat egy olyan állomány, amely (char aru[20], int mennyiség]) formátumú bejegyzéseket tartalmaz. Egyszerre több fogyasztó-, illetve termelő folyamat fog dolgozni a lerakattal. Szimuláljuk a lerakatban végzett munkát, ügyelve arra, hogy szinkronizálva legyen a lerakatba való belépés, úgy, hogy lezárjuk (lock) a lerakat állomány megfelelő részeit.

CCFLAGS = -Wall

all : r w bin

r : L12_01_bkim1790_r.o L12_01_bkim1790.h
	gcc L12_01_bkim1790_r.o -o r

L12_01_bkim1790_r.o : L12_01_bkim1790_r.c
	gcc L12_01_bkim1790_r.c -c $(CCFLAGS)

w : L12_01_bkim1790_w.o L12_01_bkim1790.h
	gcc L12_01_bkim1790_w.o -o w

L12_01_bkim1790_w.o : L12_01_bkim1790_w.c
	gcc L12_01_bkim1790_w.c -c $(CCFLAGS)

bin : L12_01_bkim1790_bin.o L12_01_bkim1790.h
	gcc L12_01_bkim1790_bin.o -o bin

L12_01_bkim1790_bin.o : L12_01_bkim1790_bin.c
	gcc L12_01_bkim1790_bin.c -c $(CCFLAGS)

.PHONY : clean
clean :
	rm -f L12_01_bkim1790_r.o L12_01_bkim1790_w.o L12_01_bkim1790_bin.o core *~
