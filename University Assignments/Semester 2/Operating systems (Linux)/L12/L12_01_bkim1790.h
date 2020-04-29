#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "lerakat.bin"
#define MINSLEEP  500000 //varakozasi ido min.
#define MAXSLEEP  900000 //illetve max. erteke (mikrosec)

typedef struct arustruktura 
{
	char aru[20];
	int mennyiseg;
} aruk;

