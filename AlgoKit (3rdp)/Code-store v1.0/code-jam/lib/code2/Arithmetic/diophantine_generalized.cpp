/*
 * Linear Diophantine Equation Solver for Any Number of Variables
 *
 * Author: Adam Beacham & Howard Cheng (gcd code) 
 *
 * Given the linear equation with integer coefficients a[i]:
 *    a[0]*x_0 + a[1]*x_1 + . . . + a[n-1]*x_n-1 = c
 *
 * It is assumed that no coefficient is 0.
 *
 * Determines whether integer solutions exist.  If they do,
 * provides a specific solution for the variables in the array sol.
 * (sol is viewed as an n-dimensional vector).
 *
 * Then bas[0], bas[1], . . ., bas[n-1] are basis vectors for the integer
 * solutions for the homogeneous equation:
 *    a[0]*x_0 + a[1]*x_1 + . . . + a[n-1]*x_n-1 = 0
 * (Each bas[i] is an n-vector).
 *
 * Thus, all solutions are given by:
 *  (x_0, . . ., x_n-1) = sol + t_0*bas[0] + . . . + t_{n-1}*bas[n-1]
 * where t_0, . . ., t_{n-1} are arbitrary integers.
 * 
 */

#include <stdio.h>
#include <assert.h>

#define MAX_VAR 5

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
 * gcd_solve
 *
 * Solves the diophantine equation 
 *   a[0]*x_0 + . . . + a[numV-1]*x_{numV-1} = gcd(a[0],...,a[numV-1])
 *
 * Given:  Coefficients in a[]
 *         number of variables in numV
 *
 * Returns:gcd of (a[0],...,a[numV-1]) as a return value
 *         specific solution in sol[]
 *         basis vectors for homogeneous solutions in bas[0],...,bas[numV-2]
 *
 * NOTE: Do NOT call this procedure except through diophantine()
 *       (Or, ensure that bas has been set to all zeroes before
 *        calling this procedure).
 */
int gcd_solve(int a[MAX_VAR], int numV, int sol[MAX_VAR], 
	      int bas[MAX_VAR-1][MAX_VAR])
{
  int ret, d, v;
  int i;

  if( numV == 2 ) {
    ret = gcd(a[0],a[1],&sol[0],&sol[1]);
    bas[0][0] = a[1]/ret;
    bas[0][1] = -a[0]/ret;
  } else if( numV > 2 ) {
    d = gcd_solve(a,numV-1,sol,bas);
    ret = gcd(d,a[numV-1],&v,&sol[numV-1]);
    for( i=0; i<numV-1; i++ ) {
      bas[numV-2][i] = a[numV-1]/ret * sol[i];
      sol[i] *= v;
    }
    bas[numV-2][numV-1] = -d/ret;
  } else {
    fprintf(stderr,"Invalid # of variables:  %d\n",numV);
    exit(1);
  }

  return ret;
}

/*
 * Solves the diophantine equation 
 *   a[0]*x_0 + . . . + a[numV-1]*x_{numV-1} = c
 * provided a solution exists.
 *
 * Given:  Coefficients in a[] (all must be non-zero)
 *         number of variables in numV
 *         RHS of equation, the constant c
 *
 * Returns:1 if a solution was found, 0 otherwise.
 *         specific solution in sol[]
 *         basis vectors for homogeneous solutions in bas[0],...,bas[numV-2]
 */
int diophantine(int a[MAX_VAR], int numV, int c, int sol[MAX_VAR], 
		int bas[MAX_VAR-1][MAX_VAR])
{
  int i,j;
  int d,q;

  for( i=0; i<numV; i++ ) {
    assert( a[i] != 0 );
  }

  for( i=0; i<numV-1; i++ ) {
    for( j=0; j<numV; j++ ) {
      bas[i][j] = 0;
    }
  }

  d = gcd_solve(a,numV,sol,bas);

  if( c % d == 0 ) {
    q = c/d;
    for( i=0; i<numV; i++ ) {
      sol[i] *= q;
    }
    return 1;
  } else {
    return 0;
  }
}


int main(void)
{
  int a[MAX_VAR];
  int sol[MAX_VAR];
  int bas[MAX_VAR-1][MAX_VAR];
  int numV;
  int i,j;
  int c;

  printf("Number of variables (MAX %d)?  ",MAX_VAR);
  scanf("%d",&numV);
  if( numV < 2 ) {
    fprintf(stderr,"Not enough variables\n");
    exit(1);
  }

  printf("Enter %d coefficients: ",numV);
  for( i=0; i<numV; i++ ) {
    scanf("%d",&a[i]);
  }
  printf("Enter constant for RHS: ");
  scanf("%d",&c);

  if( diophantine(a,numV,c,sol,bas) ) {
    printf("A specific solution to\n ");
    for( i=0; i<numV; i++ ) {
      printf(" %d*x_%d %c",a[i],i,i==numV-1 ? '=' : '+');
    }
    printf(" %d\n",c);
    printf("is:\n");
    printf("(");
    for( i=0; i<numV; i++ ) {
      printf("x_%d%c",i,i==numV-1 ? ')' : ',');
    }
    printf(" = (");
    for( i=0; i<numV; i++ ) {
      printf("%d%c",sol[i],i==numV-1 ? ')' : ',');
    }

    for( j=0; j<numV-1; j++ ) {
      printf(" + t_%d*(",j);
      for( i=0; i<numV; i++ ) {
	printf("%d%c",bas[j][i],i==numV-1 ? ')' : ',');
      }
    }
    printf("\n");

  } else {
    printf("No solution\n");
  }

  return 0;
}

