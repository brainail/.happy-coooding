#include<iostream>
#include<math.h>
#define MAX 100
using namespace std;

using namespace std;

int factors[MAX];
int times[MAX];
int total = 0;
int divisors[MAX];
int totalDivisors = 0;

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

void calcDivisor(int value, int level, int n)
{
   if(level == n) {
      if(value > 0)
         divisors[totalDivisors++] = value;
      return;
   }
   int aux = 1;
   for(int i=0; i<=times[level]; i++) {
      calcDivisor(value * aux, level+1, n);
      aux *= factors[level];
   }
}

void divisorsCalculator(int n)
{
  primeFactorization(n);
  calcDivisor(1, 0, n);
}

int main() {
   divisorsCalculator(7);
   for(int i=0; i<totalDivisors; i++)
      cout << divisors[i] << " ";
   cout << endl;
   return 0;
}
