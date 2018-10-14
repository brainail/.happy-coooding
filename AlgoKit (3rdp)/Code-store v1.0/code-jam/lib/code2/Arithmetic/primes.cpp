/*
 * Building a table of primes and finding the prime factorization of a number.
 *
 * Author: Gilbert Lee <gilbert@ugrad.cs.ualberta.ca>
 *
 * Date: 20 October 2000
 *
 * WARNING: In incoming
 */

#include <stdio.h>

#define MAX_PRIMES 10000

int primes[MAX_PRIMES/2];
int pfactor[MAX_PRIMES/2];
int psize = 0;

void GetPFactor(int x){
  int i;

  for(i = 0; i < MAX_PRIMES/2; i++) pfactor[i] = 0;

  i = 0;
 
  while(x > 1){
    if(x % primes[i] == 0){
      pfactor[i]++;
      x /= primes[i];
    } else {
      i++;
    }
  }
}

void GetPrimes(){
  int i, j;
  int isprime;

  primes[psize++] = 2;

  for(i = 3; i <= MAX_PRIMES; i+=2){
    isprime = 1;
    for(j = 1; j < psize; j++){
      if(i % primes[j] == 0){
	isprime = 0;
	break;
      }
      if((1.0)*primes[j]*primes[j] > i) break;
    }
    if(isprime) primes[psize++] = i;
  }
}

int main(){
  int i,x;
  
  GetPrimes();
  printf("There are %d primes from 1 to %d\n", psize, MAX_PRIMES);

  while(scanf("%d", &x)==1){
    GetPFactor(x);
    printf("The prime factors of %d are: ", x); 
    for(i = 0; i < psize; i++){
      if(pfactor[i] > 0) printf("%d^%d  ", primes[i], pfactor[i]);
    }  
    printf("\n");
  }
  return 0;
}


