/*Nev:Bauer Kristof
Csoport:521
1. Írjunk programot, mely egy olyan kritikus szakaszt valósít meg, amin belül a SIGQUIT és SIGINT jelzések alapértelmezett kezelője helyett egy olyan fut le, ami elmenti a jelzés számát és érkezésének időpontját. A kritikus szakaszból a SIGTERM jelzés hatására lépjen ki, és írja ki a képernyőre a kritikus szakaszban eltöltött idő során kapott jelzéseket és ezek időpontját.*/


#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <time.h>
using namespace std;

string CurrentDate()	
{
	time_t my_time = time(NULL);
	string date=ctime(&my_time);
	return date;   
}

struct signalPar
{
	int signalNumber;
	string date;
} arr[1000];
int counter=0;



void sig_handler(int signo)
{
   
  if (signo == SIGINT)
  {
    arr[counter].signalNumber=signo;
    arr[counter].date=CurrentDate();
    counter++;
  }
  else if (signo == SIGQUIT)
   {
     arr[counter].signalNumber=signo;
     arr[counter].date=CurrentDate();
     counter++;
   }
  else if(signo == SIGTERM)
  {
	  for(int i=0;i<counter;i++)
	  {
	    cout<<"Signal ID= "<<arr[i].signalNumber<<"Erkezesi ido: "<<arr[i].date<<endl;
 	  }
	  kill(getpid(),SIGKILL);
  }
}

int main()
{	
  if (signal(SIGINT, sig_handler) == SIG_ERR)
  printf("\nHIBA:Nem tudja elerni a SIGINT Jelzest\n");
  
   if (signal(SIGQUIT, sig_handler) == SIG_ERR)
  printf("\nHIBA:Nem tudja elerni a SIGINT Jelzest\n");
   
   if (signal(SIGTERM, sig_handler) == SIG_ERR)
  printf("\nHIBA:Nem tudja elerni a SIGINT Jelzest\n");


  while(1) 
    sleep(1);
  return 0;
}
