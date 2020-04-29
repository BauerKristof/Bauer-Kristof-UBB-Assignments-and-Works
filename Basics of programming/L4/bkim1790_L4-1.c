/*
Bauer Kristof
511
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_MAX 256
#define NAMES 25

void rendez(char **s,int n)
{
    int i,j;
    char *csere = (char *)malloc(S_MAX * sizeof(char));

    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
           if(strcmp( s[i],s[j]) >0)
           {
               strcpy(csere,s[i]);
               strcpy(s[i],s[j]);
               strcpy(s[j],csere);
           }
        }

    }
    free(csere);
}

void kiir(char **s, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%s\n", s[i]);
    }
}

int main()
{
    int n,i;
    FILE *f=fopen("input_L4.txt","r");
    if(!f)
    {
        printf("hiba");
        exit(1);
    }

    //1. alpont
    fscanf(f,"%d",&n);
    char **s = (char **)malloc(n * sizeof(char *));
    for(i = 0; i < n; i++)
    {
        s[i] = (char *)malloc(S_MAX * sizeof(char));
    }
    //1. Karakter matrix aminek (NAMES) sora es (S_MAX) oszlopa 5xsor 256xoszlop
    //2. String tomb aminek minden egyes eleme egy string ami lehet 256 hosszusagu
        //string tomb{{256},{256},{256},{256}}

    for(i = 0; i < n; i++)
    {
        fscanf(f, "%s\n", s[i]); //stringtombbnel nem kell &s[i] szamnal kell
    }

    kiir(s,n);
    rendez(s,n);
    kiir(s,n);

  FILE *f2=fopen("output_L4.txt","w");
    if(!f2)
    {
        printf("hiba");
        exit(1);
    }


    for(i=0; i<n;i++)
    {
        fprintf(f2,"%s\n",s[i]);
    }

    fclose(f2);


    for(i = 0; i < n; i++)
    {
        free(s[i]);
    }
    free(s);

    //2. alpont
    char c;
    int length = 1;
    char *ketstring = (char *)malloc(length * sizeof(char));
    do
    {
        fscanf(f, "%c", &c);
        ketstring[length - 1] = c;
        if(c != '\n')
        {
            length++;
            ketstring = (char *)realloc(ketstring, length * sizeof(char));
        }
    }
    while(c != '\n');
    ketstring[length - 1] = '\0';
    printf("%s\n", ketstring);
    free(ketstring);
    fclose(f);
    return 0;
}
