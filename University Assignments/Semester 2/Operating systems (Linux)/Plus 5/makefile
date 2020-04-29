.PHONY : all
all: sz kl

kl: kliens.o
	g++ -Wall kliens.o struktura.h -o kl

kliens.o: kliens.c
	g++ kliens.c -c -Wall

sz: szerver.o
	g++ -Wall szerver.o struktura.h -o sz

szerver.o: szerver.c
	g++ szerver.c -c -Wall

.PHONY : clean
clean:
	rm -f p kliens.o szerver.o core *~
