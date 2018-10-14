#include<iostream>
#include<math.h>
#define MAX 100
using namespace std;

int factors[MAX];
int total = 0;

void primeFactorization(long num)
{
     long i; //Counter
     long c; //Remaining product to factor
     c = num;
     
     while((c%2) == 0) {
        factors[total++] = 2;
        c = c/2;
     }
     i = 3;
     while(i <= (sqrt(c)+1))
        if((c%i) == 0) {
           factors[total++] = i;
           c = c/i;
        }
        else
           i = i+2;
     if(c > 1) 
        factors[total++] = c;
}

int main()
{
   primeFactorization(70);
   for(int i=0; i<total; i++)
      cout << factors[i] << " ";
   cout << endl;
   return 0;    
}

