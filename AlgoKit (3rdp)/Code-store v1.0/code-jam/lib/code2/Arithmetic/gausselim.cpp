/*
 * Compute upper echelon form and determinant of a matrix.
 *
 * Author: Richard Krueger, based on code by Howard Cheng
 * Reference:
 *  K.O. Geddes, S.R. Czapor, G. Labahn.  "Algorithms for Computer Algebra."
 *    Kluwer Academic Publishers, 1992, pages 393-399.  ISBN 0-7923-9259-0
 *
 * The routine ffgausselim takes an m x n matrix and reduces it to
 * upper echelon form. The determinant is returned for square or
 * augmented matrices.
 *
 * The algorithm is single-step fraction free Gaussian elimination.
 *
 * Date: 2 March 2000 */

#include <stdio.h>

#define MAX_N 10

int ffgausselim(int A[MAX_N][MAX_N], int m, int n)
{
  int sign, d, r, i, j, k, pivot, t;

  sign = d = 1;
  r = 0;

  for (k = 0; k < n && r < m; k++) {
    /* eliminate column k */
    
    /* find nonzero pivot */
    for (pivot = r; pivot < m && !A[pivot][k]; pivot++)
      ;
    
    if (pivot < m) {
      /* swap rows pivot and r */
      if (pivot != r) {
	for (j = k; j < n; j++) {
	  t = A[pivot][j];
	  A[pivot][j] = A[r][j];
	  A[r][j] = t;
	}
	sign *= -1;
      }

      /* do elimination */
      for (i = r+1; i < m; i++) {
	for (j = k+1; j < n; j++) {
	  A[i][j] = (A[r][k]*A[i][j]-A[i][k]*A[r][j])/d;
	}
	A[i][k] = 0;
      }
      d = A[r][k];
      r++;
    }
  }

  if (r == m)
    return sign*d;
  else
    return 0;
}

int main(void)
{
  int A[MAX_N][MAX_N];
  int m,n, i, j;
  int det;

  while (scanf("%d%d", &m, &n) == 2 &&
	 0 < m && m <= MAX_N && 0 < n && n <= MAX_N) {
    printf("Enter A:\n");
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
	scanf("%d", &A[i][j]);
      }
    }
    det = ffgausselim(A, m, n);
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
	printf("%d ", A[i][j]);
      }
      printf("\n");
    }
    printf("det = %d\n", det);
  }
  return 0;
}


