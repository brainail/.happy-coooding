/*
 * Generate de Bruijn sequence
 *
 * Author: Richard Krueger
 * Reference: none
 *
 * Description:
 * A de Bruijn sequence contains every subsequence of N characters over
 * an alphabet of K characters.
 * The program will compute the alphabetically first de Bruijn sequence
 * for the given N,K pair. We do an in-order traversal of the transition
 * graph, where each transistion is adding a letter to the end of a string and
 * removing the first letter. This graph is implicitly created -- all we
 * really track is which letter (transisition) to take next from each node.
 * The transitions we take, starting from the alphabetically last node
 * gives us the de Bruijn sequence. There are K^N letters in the
 * de Bruijn sequence.
 *
 * Date: 27 March 1999
 * Commented: 15 June 1999
 *
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define MAXN 10240

int
main()
{
  int n,k,h,i,m;
  char * u;
  char s[MAXN];

  while (scanf("%d %d", &n, &k) == 2) {
    assert(n <= MAXN);
    if (n == 1) {
      /* special case: strings are only one letter long */
      for (i = 0; i < k; i++)
	putchar('0'+i);
    } else {
      for (i = 0; i < n-1; i++)
	s[i] = k-1;

      /* this is where we keep the next transition for each node */
      u = calloc(pow(k, n-1),1);
      for (h=0; h<pow(k,n); h++) {
	m = 0;
	for (i=0; i<n-1; i++) {
	  m *= k;
	  m += s[(h+i)%(n-1)];
	}
	putchar('0' + u[m]);
	s[h%(n-1)] = u[m];
	u[m]++;
      }
    }
    putchar('\n');
  }
  return 0;
}

