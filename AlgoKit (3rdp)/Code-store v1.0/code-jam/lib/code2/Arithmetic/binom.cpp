/*
 * Binomial Coefficient
 *
 * Author: Richard Krueger <richard@cs.ualberta.ca>
 * Reference: Rewrote incorrect code that Howard found on Internet.
 *
 * This routine computes the binomial coefficient without overflow,
 * provided that C(n,k) < ULLONG_MAX.
 *
 * The input must satisfy 0 <= k <= n.
 *
 * Note: limit for unsigned long is C(35,16) = C(35,19)
 *       C(35,17) = C(35,18) = 4537567650 > ULONG_MAX
 * Note: limit for unsigned long long is C(68,30) = C(68,38)
 *       C(68,31), ..., C(68,37) > ULLONG_MAX
 * All coefficients with smaller n values work without overflow.
 *
 * Date: 7 March 2000
 * Edited: 30 October 2000 - corrected overflow error <richard@cs>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int gcd(int a, int b){
   int r;
   while (b) {
     r = a % b;
     a = b;
     b = r;
   }
   return a;
}

/* use whichever data type you need */
/* #define unum unsigned long */
#define unum unsigned long long

unum binom(int n, int k){
   unum cnm = 1UL;
   int i, g;
   
   if (k > n/2) k = n-k;
   for (i=1; i <= k; n--, i++) {
     g = gcd(n,i);
     cnm /= i/g;
     cnm *= n/g;
   }
   return cnm;
}

int main (){
   int n,k;
   
   while (scanf("%d%d", &n, &k) == 2)
     printf ("%d choose %d = %llu\n", n, k, binom(n,k));
   
   return 0;
}

