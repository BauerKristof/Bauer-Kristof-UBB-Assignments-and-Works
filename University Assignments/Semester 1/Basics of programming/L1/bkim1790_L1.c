/*Bauer Kristof
511
bkim1790*/

#include <stdio.h>

int isNumber(char c)
{
    if(c>='0'&& c<='9')
    {
        return 1;
    }
    return 0;
}

int main()
{
FILE *f=fopen("input_L1.txt","r");
if(!f)
{

    printf("error1\n");
    exit(1);
}
else
{
    int n;
    int r;

    char c[4];
//r=fscanf(f,"%d",&n);
r=fscanf(f,"%c\t%c\t%c\t\%c",&c[0],&c[1],&c[2],&c[3]);
fclose(f);

//if(r!=1)
if(r!=4)
{
    printf("Error 2\n");
    exit(2);
}
f=fopen("output_L1.txt","w");


//printf("A szam %d\n",n);
//fprintf(f,"%d",n);

int i;
int sz[3];
int j=0;
char k;

for(i=0;i<4;i++)
{
    if(isNumber(c[i]))
    {
    sz[j]=c[i]-'0';
    j++;
    }
    else
    {
        k=c[i];
    }
}

fprintf(f,"A szamok: %d %d %d\n",sz[0],sz[1],sz[2]);
fprintf(f,"A betu %c",k);

if(k>='a' && k<='z')
{
    fprintf(f," kisbetu\n");
}
else
{

    if(k>='A' && k<='Z')
    {
        printf(f," Nagybetu \n");
    }
    else
    {

        printf(f," Ismeretlen karakter \n");
    }
}
fprintf(f,"%d %d %d %s haromszoget \n",sz[0],sz[1],sz[2],(sz[0]+sz[1]>sz[2] && sz[0]+sz[2]>sz[1] && sz[1]+sz[2]>sz[0]) ?"alkothat":"nem alkothat");
fclose(f);



}

return 0;
}
