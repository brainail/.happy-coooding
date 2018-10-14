/*
 * Gray code
 *
 * Author: Matthew McNaughton
 * References:
 *   Adam Beacham. I don't know where he got it. ;)
 *
 * Description:
 * Generates a b-bit gray code starting from 0.
 *
 * Date: 1999-11-16.
 */

#include <stdio.h>

char *
pbits(char *s, int n, int b) {
  unsigned int i; char *t;
  t = s;
  for( i = 1 << (b-1); i != 0; i >>= 1 ) {
    *s++ = n&i ? '1' : '0';
  }
  *s++ = '\0';
  return t;
}

/* the i'th gray code is i^(i>>1). Magic. */
/* Takes one integer b on standard input.
 * Generates a b-bit gray code starting from 0. */

int
main() {
  unsigned int i;
  int n;
  char s[512];

  scanf("%d", &n);

  for( i = 0; i < (1 << n); i++ ) {

    printf("%s\n", pbits(s, i^(i>>1), n));
  }
  return 0;
}


