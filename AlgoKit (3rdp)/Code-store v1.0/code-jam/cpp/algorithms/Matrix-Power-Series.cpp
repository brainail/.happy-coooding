/*
 *	Matrix Power Series Problem.
 *	Description:
 *		Given a n*n matrix A and a positive integer k(k < 10^9), 
 *		find the sum S = A + A^2 + A^3 + бн + A^k.
 *
 *	Algorithm:
 *		Method 1, suppose f[n]=A^1+A^2+....A^n;
 *		    if (n is even) f[n]=f[n/2]+f[n/2]*A^(n/2);
 *		    if (n is odd)  f[n]=f[n-1]+A^(n);
 *		
 *		Method 2, Let B= [A I]
 *						 [0 I];
 *			B^(k+1) = [A^k   I+A+...+A^k];
 *					  [ 0         I     ]
 *			
 *	Problems:
 *		poj 3233.
 * */

#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXD = 30;

int N, K, M;

struct Matrix {
	int matrix[MAXD][MAXD];
	Matrix() {
		memset(matrix, 0, sizeof(matrix));
	}
}A, E;

void init() {
	memset(E.matrix, 0, sizeof(E.matrix));
	for (int i = 0; i < MAXD; i++) E.matrix[i][i] = 1;
}

void input() {
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			scanf("%d", &A.matrix[i][j]);
}

Matrix add(const Matrix &a, const Matrix &b)
{
    Matrix c;
    int i,j;
    for(i = 0; i < MAXD; i++)
        for(j = 0; j < MAXD; j++)
            c.matrix[i][j] = (a.matrix[i][j] + b.matrix[i][j]) % M;
    return c;
}

Matrix mul(const Matrix &A, const Matrix &B) {
	Matrix C;
	int i, j, k;
	LL tmp;
	for (i = 0; i < MAXD; i++)
		for (j = 0; j < MAXD; j++) {
			tmp = 0;
			for (k = 0; k < MAXD; k++) {
				tmp += A.matrix[i][k] * B.matrix[k][j];
			}
			C.matrix[i][j] = tmp % M;
		}
	return C;
}

Matrix pow(const Matrix M, int p) {
	if (p == 0) {
		Matrix e;
		for (int i = 0; i < MAXD; i++) e.matrix[i][i] = 1;
		return e;
	} else {
		Matrix res = pow(M, p / 2);
		res = mul(res, res);
		if (p % 2) res = mul(res, M);
		return res;
	}
}

Matrix solve(int k) 
{
    if(k == 0) return E;
    if(k == 1) return A;
    if(k & 0x1) {
        return add(A, mul(A, solve(k-1)));
    } else {
        Matrix C = solve(k >> 1);
        return add(C, mul(pow(A, k>>1),C));
    }
}

int main() {
	init();
	while (scanf("%d%d%d", &N, &K, &M) != EOF) {
		input();
		Matrix ans = solve(K);
		int i, j;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				printf("%d", ans.matrix[i][j]);
				if (j == N-1) printf("\n");
				else printf(" ");
			}
		}
	}
return 0;
}



