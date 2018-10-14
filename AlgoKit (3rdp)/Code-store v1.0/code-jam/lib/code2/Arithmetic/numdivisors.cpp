/*
 * Count number of factors in a range
 *
 * Author: unknown, not Howard :)
 * References:
 *  some code stolen from GNU sh-utils factor.c
 *  This is a solution to #294 on the Spanish Site
 *
 * Description: Good luck reading it.
 *  Finds the number P which has the largest number of divisors (if
 *  several numbers tie for first place, selects the lowest), and the
 *  number of positive divisors D of P (where P is included as a divisor).
 *  (Range limit is about 10,000, location of range is unlimited.)
 *
 * Commented by: Richard Krueger 15 June 99
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

/* preconditions: n0 > 0, curmax >= 0 */
/* returns the number of divisors of n0. if n0 has less than
   curmax divisors, may return 0. */
static
int numdivisors(int n0, int curmax) {
  unsigned int n,fcount,divcount,d,sqrt_n;

  if( n0 == 1 ) return 1;
  
  n = n0;
  fcount = 0;
  while (n % 2 == 0) {
    fcount++;
    n /= 2;
  }

  divcount = fcount + 1;

  sqrt_n = (unsigned int) sqrt ((double) n);

  for (d = 3; d <= 101; d += 2) {
    fcount = 0;
    while (n % d == 0) {
      fcount ++;
      n /= d;
    }
    if( fcount ) divcount *= fcount + 1;
  }

  /* prune now: if divcount * 2^\ceil{{log_d n}} < curmax, can't beat curmax. */
  if( divcount * (1 << (int)ceil(log(n)/log(d))) < curmax ) return 0;

  for (; d <= sqrt_n; d += 2) {
    fcount = 0;
    while (n % d == 0) {
      fcount ++;
      n /= d;
    }
    if( fcount ) divcount *= fcount + 1;
  }

  if (n != 1 || n0 == 1) {
    divcount *= 2;
  }

  return divcount;
}

int
main() {
  int i,ncases,start,end,j,maxdivisors,numdivs,maxdivnum;

  fscanf(stdin, "%d", &ncases);
  for( i = 0; i < ncases; i++ ) {

    fscanf(stdin, "%d %d", &start, &end);
    maxdivisors = 0;

    for( j = start; j <= end; j++ ) {
      numdivs = numdivisors(j,maxdivisors);
      if( numdivs > maxdivisors ) {
	maxdivisors = numdivs;
	maxdivnum = j;
      }

    }
    printf("Between %d and %d, %d has a maximum of %d divisors.\n",
	   start, end, maxdivnum, maxdivisors);
  }
  return 0;
		       
}
