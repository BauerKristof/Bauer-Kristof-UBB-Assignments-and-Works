#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define S_MAX 256
#define NAMES 5

int main()
{
        int n,i;
    FILE *f=fopen("input_L2.txt","r");
    if(!f)
    {
        printf("hiba");
        exit(1);
    }

    fscanf(f,"%d",&n);
    char s[NAMES][S_MAX];
    //1. Karakter matrix aminek (NAMES) sora es (S_MAX) oszlopa 5xsor 256xoszlop
    //2. String tomb aminek minden egyes eleme egy string ami lehet 256 hosszusagu
        //string tomb{{256},{256},{256},{256}}

    for(i=0;i<NAMES;i++)
    {
        fscanf(f,"%s", s[i]); //stringtombbnel nem kell &s[i] szamnal kell
    }

    fclose(f);

    f=fopen("output_L2.txt","w");

    fprintf(f,"%d\n",n);
    for(i=0; i<NAMES;i++)
    {
        fprintf(f,"%s\n",s[i]);
    }

    fclose(f);

    int M[n][n]; //1-tol mn
    int T[n*n];
    int j,K = 0;

    for(i=0;i<n*n;i++)
    {
        M[i/n][i%n]=i+1;
    }

    f=fopen("output_L2.txt","w");
    fprintf(f,"M[%d][%d]\n",n,n);

    for(i=0;i<n*n;i++)
    {
        fprintf(f,"%d\t",M[i/n][i%n]);
        if(i%n ==n-1)
        {
            fprintf(f,"\n");
        }
    }

    for(i=0;i<=n/2;i++)
    {
        for( j=i; j<n-i; j++)
        {
            T[K]=M[i][j];
            K++;

        }

        for(j=i+1; j<n-i-1;j++)
        {
            T[K]=M[j][n-i-1];
            K++;
        }

        for(j=n-i-1;j>i;j--)
        {
            T[K]=M[n-i-1][j];
            K++;
        }

        for(j=n-i-1;j>i;j--)
        {
            T[K]=M[i][j];
            K++;
        }
    }

    fprintf(f,"\n\nT[%d]:\n",n*n);

    for(i=0;i<n*n;i++)
    {
      fprintf(f,"%d\t",T[i]);
    }



    //2. alpont

    int k1,k2;
    fprintf(f,"\n\n\t\t");
    int end;
    srand(time(NULL));


    for(i=0; i<NAMES;i++)
    {
        fprintf(f,"%s\t",s[i]); //kiir nyertes
    }
    fprintf(f,"\n");

    for(i=0;i<n*NAMES;i++)
    {
        fprintf(f,"%d. kor\t",  i + 1);
        for(j=0;j<NAMES;j++)
        {
            if(j==i%NAMES)
            {
                fprintf(f,"  -  \t");
                continue;
            }
            k1=rand()%6+1;
            k2=rand()%6+1;
            fprintf(f,"(%d,%d)\t",k1,k2);

            if(k1==6 && k2==6)
            {
                fprintf(f,"\nA nyertes %s.\nA jatek %d korben veget ert",s[j],i+1);
                end=1;
                break;
            }

        }
            fprintf(f, "\n");
         if(end)
            {
                break;
            }
    }
    if(!end)
            {
                fprintf("Mindenki nyert. A jatek a %d korben ert veget",n*NAMES);
            }


    fclose(f);



    return 0;
}
