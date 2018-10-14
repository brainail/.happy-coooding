/*
 * Big integer implementation
 *
 * Author: Howard Cheng
 *
 * Each digit in our representation represents LOG_BASE decimal digits
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

/* MAX_DIGIT should be defined to ensure that there is no overflow     */
/* should be safe if it is one or two digits more than the specified   */
/* bound.                                                              */
#define MAX_DIGIT 60
#define BASE 10000
#define LOG_BASE 4
#define FMT_STR "%04d"

typedef int BigNum[MAX_DIGIT];

/*
 * For all operations taking a "result" parameter, it cannot be the
 * same as one of the operands unless stated otherwise.
 *
 */

/* a = b */
static void copy(BigNum a, BigNum b);

/* a = 0 */
static void clear(BigNum a);

/* a == 0 */
static int is_zero(BigNum a);

/*
 * return   1 if a > b
 *          0 if a = b
 *         -1 if a < b	
 */
static int compare(BigNum a, BigNum b);

/* result = a + b,
 * result can be the same as one of the operands
 */
static void add(BigNum a, BigNum b, BigNum result);

/* result = a - b,
 * result can be the same as one of the operands
 * assumes a >= b
 */
static void subtract(BigNum a, BigNum b, BigNum result);

/* a++ */
static void inc(BigNum a);

/* a--, assumes a > 0 */
static void dec(BigNum a);

/* a <<= amount, or a = a*BASE^amount */
static void lshift(BigNum a, int amount);

/* result = a * b, where b is a single digit */
static void mult_digit(BigNum a, int b, BigNum result);

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result);

/* result = x^y, y must be an integer */
static void power(BigNum x, int y, BigNum result);

/* q = a / b, r = a % b */
static void divide(BigNum a, BigNum b, BigNum q, BigNum r);

/* read BigNum from stdin */
static void read_num(BigNum a);

/* write BigNum to stdout */
static void write_num(BigNum a);

int main(void)
{
  BigNum a, b, c, q, r;
  int count;
  int limit = 100;

  srand(time(NULL));
  for (count = 0; count < limit; count++) {
    /* generate random a and b */
    int l1, l2, i;
    clear(a);
    clear(b);
    l1 = rand() % (MAX_DIGIT-1);
    l2 = rand() % (MAX_DIGIT-1);
    for (i = 0; i < l1; i++) {
      a[i] = rand() % BASE;
    }
    b[0] = rand() % (BASE-1) + 1;
    for (i = 1; i < l2; i++) {
      b[i] = rand() % BASE;
    }
    if (count % 10 == 0) {
      printf("count = %d\n", count);
      fflush(stdout);
    }
    divide(a, b, q, r);
    mult(b, q, c);
    add(c, r, c);
    if (compare(a, c) != 0) {
      printf("count = %d\n", count);
      printf("a = "); write_num(a); printf("\n");
      printf("b = "); write_num(b); printf("\n");
      printf("q = "); write_num(q); printf("\n");
      printf("r = "); write_num(r); printf("\n");
      printf("b*q+r = "); write_num(c); printf("\n");
      exit(1);
    }
  }
  printf("All tests passed.\n");
  return 0;
}

/* perform assignment a = b */
static void copy(BigNum a, BigNum b)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = b[i];
  }
}

/* perform assignment a = 0 */
static void clear(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = 0;
  }
}

/* perform comparison a == 0 */
static int is_zero(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    if (a[i]) {
      return 0;
    }
  }
  return 1;
}

/* perform comparison between a and b.
   Returns -1 if a < b
            0 if a == b
           +1 if a > b */
static int compare(BigNum a, BigNum b)
{
  int i;
  for (i = MAX_DIGIT-1; i >= 0; i--) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

/* performs result = a + b */
static void add(BigNum a, BigNum b, BigNum result)
{
  int sum, carry, i;
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    sum = a[i] + b[i] + carry;
    result[i] = sum % BASE;
    carry = (sum >= BASE) ? 1 : 0;
  }
  assert(carry == 0);       /* assert no overflow */
}

/* perform result = a - b.  assumes a >= b */
static void subtract(BigNum a, BigNum b, BigNum result)
{
  int diff, borrow, i;
  borrow = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    diff = a[i] - b[i] - borrow;
    result[i] = (diff >= 0) ? diff : diff + BASE;
    borrow = (diff < 0) ? 1 : 0;
  }
  assert(borrow == 0);
}

/* perform a++ */
static void inc(BigNum a)
{
  BigNum one;
  clear(one);
  one[0] = 1;
  add(a, one, a);
}

/* perform a--, assumes a > 0 */
static void dec(BigNum a)
{
  BigNum one;
  clear(one);
  one[0] = 1;
  subtract(a, one, a);
}

/* perform a *= BASE^amount */
static void lshift(BigNum a, int amount)
{
  int i;

  if (amount <= 0) {
    return;
  }

  for (i = MAX_DIGIT-1; i >= amount; i--) {
    a[i] = a[i-amount];
  }
  for (i = 0; i < amount; i++) {
    a[i] = 0;
  }
}

/* result = a * b, where b is a single digit */
static void mult_digit(BigNum a, int b, BigNum result)
{
  int i, carry;
  int prod;

  assert(0 <= b && b < BASE);
  clear(result);
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    prod = b * a[i];
    result[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  assert(carry == 0);
}

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result)
{
  int i;
  BigNum temp1, temp2;

  clear(result);

  for (i = 0; i < MAX_DIGIT; i++) {
    if (b[i] != 0) {
      copy(temp1, a);
      lshift(temp1, i);
      mult_digit(temp1, b[i], temp2);
      add(temp2, result, result);
    }
  }
}

/* result = x^y, y must be an integer */
static void power(BigNum x, int y, BigNum result)
{
  BigNum sx, t;

  clear(result);
  inc(result);
  copy(sx, x);

  while (y > 0) {
    if (y & 0x01) {
      y--;
      mult(result, sx, t);
      copy(result, t);
    } else {
      y >>= 1;
      mult(sx, sx, t);
      copy(sx, t);
    }
  }
}

/* q = a / b, r = a % b */
static void divide(BigNum a, BigNum b, BigNum q, BigNum r)
{
  BigNum one, t, q_temp, t2, q_temp2, t3, q_temp3;
  int shift;

  assert(!is_zero(b));
  clear(one);
  inc(one);

  copy(r, a);
  clear(q);

  while (compare(r, b) >= 0) {
    /* find biggest shift t of b st t <= r */
    copy(t, b);
    lshift(t, 1);
    shift = 0;
    while (compare(t, r) <= 0 && shift < MAX_DIGIT-1) {
      shift++;
      lshift(t, 1);
    }

    /* we do the shifts */
    copy(t, b);
    lshift(t, shift);
    copy(q_temp, one);
    lshift(q_temp, shift);

    mult_digit(t, 2, t2);
    mult_digit(q_temp, 2, q_temp2);
    mult_digit(t, 4, t3);
    mult_digit(q_temp, 4, q_temp3);

    /* now start subtracting as much as possible */
    while (compare(r, t3) >= 0) {
      subtract(r, t3, r);
      add(q, q_temp3, q);
    }
    while (compare(r, t2) >= 0) {
      subtract(r, t2, r);
      add(q, q_temp2, q);
    }
    while (compare(r, t) >= 0) {
      subtract(r, t, r);
      add(q, q_temp, q);
    }
  }
}

/* read BigNum from stdin */
static void read_num(BigNum a)
{
  char buffer[1024];     /* increase if necessary */
  int i, j, k, t, len, limit, mult;

  t = scanf("%s", buffer);
  assert(t == 1);
  len = strlen(buffer);
  clear(a);

  if (len % LOG_BASE == 0) {
    limit = len / LOG_BASE;
  } else {
    limit = len / LOG_BASE + 1;
  }

  j = len-1;
  for (i = 0; i < limit; i++) {
    mult = 1;
    for (k = 0; k < LOG_BASE; k++) {
      if (j >= 0) {
        a[i] += (buffer[j] - '0') * mult;
      }
      j--;
      mult *= 10;
    }
  }
}

/* write BigNum to stdout */
static void write_num(BigNum a)
{
  int i, k, writing;

  if (is_zero(a)) {
    printf("0");
  } else {
    k = 0;
    writing = 0;
    for (i = MAX_DIGIT-1; i >= 0; i--) {
      assert(0 <= a[i] && a[i] < BASE);
      if (writing) {
        printf(FMT_STR, a[i]);
      } else if (a[i]) {
        printf("%d", a[i]);
        writing = 1;
      }
    }
  }
}
