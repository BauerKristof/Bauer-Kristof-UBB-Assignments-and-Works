#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headerfile.h"

//Nev:Bauer Kristof
//Csoport:511
//Felhasznalo:bkim1790
//Feladat csoport:L8
//Feladat szama=1
//Feladat:Írjunk egy „gyok(k, a)” függvényt


int main(int argc, const char * argv[])
{
        FILE* f;
        FILE* o;
        f = fopen("input.dat", "r");
        if(f == NULL)
        {
                printf("HIBA: Bemeneti filenal! ");
                return 0;
        }

        if(argv[1]==NULL)
        {
        printf("HIBA: Nincs argumentum megadva\n");
        return 0;
        }

        if(atoi(argv[1])<=2)
        {
        printf("HIBA:Helytelen argumentum. Min. 2 kell legyen\n");
        return 0;
	}

        o = fopen("output.dat", "w");

        int n, i;
        float S=0;
        int k = atoi(argv[1]);


        fscanf(f, "%d", &n);
        float* a=(float*)malloc(n*sizeof(float));

        for (i = 0; i < n; i++)
        {
                fscanf(f, "%f", &a[i]);
        }


        for (i = 0; i < n; i++)
        {
                S += gyok(k, a[i]);
        }

        fprintf(o,"Az eredmeny=%f\n", S);
        free(a);
        fclose(f);
        fclose(o);

        return 0;
}

