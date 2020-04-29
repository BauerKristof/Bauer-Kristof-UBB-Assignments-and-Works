CCFLAGS = -Wall

all: sz kl

sz : L11_01_bkim1790_sz.o struktura.h
	gcc L11_01_bkim1790_sz.o -o sz

L11_01_bkim1790_sz.o : L11_01_bkim1790_sz.c
	gcc L11_01_bkim1790_sz.c -c $(CCFLAGS)

kl : L11_01_bkim1790_kl.o struktura.h
	gcc L11_01_bkim1790_kl.o -o kl

L11_01_bkim1790_kl.o : L11_01_bkim1790_kl.c
	gcc L11_01_bkim1790_kl.c -c $(CCFLAGS)

.PHONY : clean
clean :
	rm -f p L11_01_bkim1790_sz.o L11_01_bkim1790_kl.o core *~
