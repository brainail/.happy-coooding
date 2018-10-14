#include<iostream>
#include<math.h>
#define MAX 100
using namespace std;

using namespace std;

int factors[MAX];
int times[MAX];
int total = 0;

long insertFactor(long lastFact, long actualFact)
{
   if(lastFact != actualFact) {
      factors[total] = actualFact;
      times[total]  = 1;
   }
   else
      times[total]++;
   total += 1;
   return actualFact;
}

void primeFactorization(long num)
{
     long i; //Counter
     long c; //Remaining product to factor
     long last = -1;
     
     c = num;
     
     while((c%2) == 0) {
        last = insertFactor(last, 2);
        c = c/2;
     }
     i = 3;
     while(i <= (sqrt(c)+1))
        if((c%i) == 0) {
           last = insertFactor(last, i);
           c = c/i;
        }
        else
           i = i+2;
     if(c > 1) 
        last = insertFactor(last, c);
}


int totalDivisors(long n)
{
  int divisors = 1;

  primeFactorization(n);
  for(int i=0; i<total; i++)
    divisors *= times[i]+1;
  return divisors;
}

int main() {
   cout << totalDivisors(820);
   return 0;
}
