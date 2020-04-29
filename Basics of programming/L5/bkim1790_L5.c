#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Gyerek
{
   char  nev[50];
   int kor;
   char jo[5];
};


int main()
{
    FILE *f = fopen("input.txt", "r");
    FILE *f2 = fopen("config.txt", "r");
    int i=0, j=0,n=5,opcio;
    char joe[5];


    if(!f)
    {
        printf("Nem tudom megnyitni a filet");
        exit(1);
    }

    struct Gyerek *a=(struct Gyerek*) malloc(n*sizeof(struct Gyerek));

    for(i=0;i<n;i++)
    {
        fscanf(f,"%s%d%s", a[i].nev, &a[i].kor,a[i].jo);
    }

    for(i=0; i<n;i++)
    {
        printf("%s\t%d\t%s\n",a[i].nev,a[i].kor,a[i].jo);
    }
    close(f);

    if(!f2)
    {
     printf("Hibas file path");
     exit(1);
    }
    else
    {
        fscanf(f2,"%d",&opcio);
       if((opcio<1) || (opcio>5))
        {
        printf("Hibas a file bemenet, ird at\n");
        exit(1);
        }
    }
    close(f2);
    if(opcio==1)
    {
         printf("\n");
        struct Gyerek seged;

        for(i=0; i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(strcmp( a[i].nev,a[j].nev) >0)
                {
                seged=a[i];
                a[i]=a[j];
                a[j]=seged;
                }
            }
        }

    for(i=0; i<n;i++)
    {
        printf("%s\t%d\t%s\n",a[i].nev,a[i].kor,a[i].jo);
    }

    }

    if(opcio==2)
    {
         printf("\n");
        struct Gyerek seged;

        for(i=0; i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                if(a[i].kor<a[j].kor)
                {
                seged=a[i];
                a[i]=a[j];
                a[j]=seged;
                }
            }
        }

    for(i=0; i<n;i++)
    {
        printf("%s\t%d\t%s\n",a[i].nev,a[i].kor,a[i].jo);
    }

    }

    if(opcio==3)
    {
        printf("\n");
        char csere[3]="jo";

        for(i=0; i<n;i++)
        {
         if(strcmp(a[i].jo,csere) == 0)
         {
          printf("%s\t%d\t%s\n",a[i].nev,a[i].kor,a[i].jo);
         }
        }
    }

    if(opcio==4)
    {

        printf("\n");
        char csere[3]="jo";

        for(i=0; i<n;i++)
        {
         if(strcmp(a[i].jo,csere) > 0)
         {
          printf("%s\t%d\t%s\n",a[i].nev,a[i].kor,a[i].jo);
         }
        }
    }


    return 0;
}
