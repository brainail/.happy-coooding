/*
 * Simpson's Rule for Numerical Integration
 *
 * Reference:  any Calculus book.
 *
 * Numerical integration of the function f from a to b.
 * Splits the interval [a,b] into 2k pieces.
 *
 * The error is <= (b-a)/180.0 * M * h^4
 * where:
 *   M = max( abs(f''''(x)) ) for x in [a,b]
 *   h = (b-a)/2k
 *
 * Note that this means that the integrals for low degree polynomials
 * are computed exactly.
 *
 * by Adam Beacham, Jan 1999
 */

#include <assert.h>
#include <stdio.h>
#include <math.h>     /* needed for the example function */

/*
 * Numerical integration of the function f from a to b.
 * Splits the interval [a,b] into 2k pieces.
 *
 * The error is <= (b-a)/180.0 * M * h^4
 * where:
 *   M = max( abs(f''''(x)) ) for x in [a,b]
 *   h = (b-a)/2k
 *
 * Note that this means that the integrals for low degree polynomials
 * are computed exactly.
 */
double Simpson(double a, 
	       double b, int k, double (*f)(double))
{
  double dx;
  int i;
  double total;
  double x;

  assert( (a - b) != 0 && k > 0);

  dx = (b-a)/(2.0*k);

  total = 0;

  for( i=0; i<k; i++ ) {
    total += (i==0 ? 1.0 : 2.0) * (*f)(a+2.0*i*dx);
    total += 4.0 * (*f)(a+(2.0*i+1.0)*dx);
  }
  total += (*f)(b);

  return total * (b-a)/6.0/k;
}

double x2(double x)
{
  return exp(-x*x)*sin(x);
}

int main(void)
{
  int k;
  double a = 0, b=M_PI/2.0;

  printf("Integral from %f to %f is:\n",a,b);
  for( k=1; k<=40; k++ ) {
    printf("  k = %3d:  %f\n",k,Simpson(a,b,k,x2));
  }

  return 0;
}
