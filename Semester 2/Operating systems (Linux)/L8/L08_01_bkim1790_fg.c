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

float gyok(int k, float a)
{
        float x = a; //x0
        float y = (1.0 / k)*((k - 1)*(a / 2.0) + (a / pow(a / 2, k - 1)));//x1

        while (fabs(x - y) >= 0.00000001)
        {
                x = y;
                y = (1.0 / k)*((k - 1)*(x)+(a / pow(x, k - 1)));
        }
        return y;
}

