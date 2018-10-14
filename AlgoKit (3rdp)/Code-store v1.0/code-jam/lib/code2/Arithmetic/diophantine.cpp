/*
 * Linear Diophantine Equation Solver
 *
 * Author: Adam Beacham & Howard Cheng (gcd code) 
 *
 * Given the linear equation with integer coefficients:
 *    ax + by = c
 *
 * NOTE:  Only one of a and b can be 0!
 *
 * Determines whether integer solutions exist.  If they do,
 * provides the values as
 *  x = x0 + n*x_step
 *  y = y0 + n*y_step
 *
 * where n is allowed to vary over the integers.
 */

#include <stdio.h>
#include <assert.h>

int gcd(int a, int b, int *s, int *t)
{
  int r, r1, r2, a1, a2, b1, b2, q;
  int A = a;
  int B = b;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    r = gcd(-a, b, s, t);
    *s *= -1;
    return r;
  }
  if (b < 0) {
    r = gcd(a, -b, s, t);
    *t *= -1;
    return r;
  }

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    assert(a1*A + a2*B == a);
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }

  *s = a1;
  *t = a2;
  assert(a >= 0);
  return a;
}

/*
 * Given:  Integer cofficients a,b,c of equation ax+by=c
 * 
 * RETURNS:  0 if no solution exists
 *           1 if a solution exists.
 *
 * If solutions exist, x = x0 + n*x_step
 *                     y = y0 + n*y_step
 * where n may be any integer.
 */
int diophantine(int a, int b, int c,
		int *x0, int *x_step, int *y0, int *y_step)
{
  int d;
  int q;

  assert( a != 0 || b != 0 );

  d = gcd(a,b,x0,y0);
  
  if( c % d == 0 ) {
    q = c/d;
    *x0 *= q;
    *y0 *= q;
    *x_step = (b/d);
    *y_step = (-a/d);
    return 1;
  } else {
    /* no solution */
    return 0;
  }    
}

int main(void)
{
  int a, b, c, x0, y0, x_step, y_step, x,y,i;

  while (scanf("%d %d %d", &a, &b, &c) == 3) {
    printf("The equation %dx + %dy = %d has ",a,b,c);
    if( diophantine(a,b,c,&x0,&x_step,&y0,&y_step) ) {
      printf("solutions of the form:\n");
      printf("   x = %d + n * %d\n",x0,x_step);
      printf("   y = %d + n * %d\n",y0,y_step);
      printf("\nFor instance,\n");
      for( i=-5; i<=5; i++ ) {
	x = x0 + i*x_step;
	y = y0 + i*y_step;
	printf("  n =%3d:  %d(%d) + %d(%d) = %d\n",i,a,x,b,y,a*x+b*y);
      }
      printf("\n");
    } else {
      printf("no solutions.\n\n");
    }
  }
  return 0;
}

