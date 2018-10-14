/*
 *	Q-Matrix Problem.
 *	Description:
 *		F[1], F[2], ...... F[d] is already know. A[1], A[2], ...... A[d] is given.
 *		F[n] = A[1] * F[n-1] + A[2] * F[n-2] + ...... + A[d] * F[n-d].
 *		Your task is to calculate F[n] % M.
 *
 *	Algorithm:
 *		Set vector v = {F[1], F[2], ..., F[n]}
 *		Design a matrix e where vv = v * e = {F[2], F[3], ..., F[n+1]};
 *		Suppose w[i] is the column of e, col[i] : v[i] *w[i] = vv[i].
 *		So the matrix is like this:
 *		 _                  _
 *		|  0 0 ... 0 A[d]    |
 *		|  1 0 ... 0 A[d-1]  |
 *		|  0 1 ... 0 A[d-2]  |
 *		|  . .     . .       |
 *		|  . .     . .       |
 *		|  . .     . .       |
 *		|_ 0 0 ... 1 A[1]   _|
 *		
 *		v * e^n = { ... F[n]}
 *		To calculate e^n there is log(n) algorithm.
 *
 *	Problems:
 *		uva10870.
 * */

// This problem is from 2008 beijing preliminary online contest hosted by bjtu.
// Problem ID is 1007. It slightly diff from uva10870, but the main algorithm is the same.

#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 9973;
const int MAXD = 5;

struct Matrix {
	int matrix[MAXD][MAXD];
	Matrix() {
		memset(matrix, 0, sizeof(matrix));
	}
}E;

struct Array {
	int array[MAXD];
}A, F;

void input() {
	int i, j;
	// input A[0] ... A[D-1].
	for (i = 0; i < MAXD; i++) scanf("%d", &A.array[i]);
	// calculate F[0] ... F[4], F[0] is given, F[k] = 0 (k < 0);
	scanf("%d", &F.array[0]);
	for (i = 1; i < MAXD; i++) {
		F.array[i] = 0;
		for (j = MAXD; j > 0; j--) 
			if (i - j >= 0) {
				F.array[i] = (F.array[i] + F.array[i-j] * A.array[MAXD-j]) % MOD;
			}
	}
}

void build_matrix() {
	memset(E.matrix, 0, sizeof(E.matrix));
	int i;
	for (i = 0; i < MAXD-1; i++) E.matrix[i+1][i] = 1;
	for (i = 0; i < MAXD; i++) E.matrix[i][MAXD-1] = A.array[i];
}

Matrix mul(const Matrix &A, const Matrix &B) {
	Matrix C;
	int i, j, k;
	for (i = 0; i < MAXD; i++)
		for (j = 0; j < MAXD; j++) {
			C.matrix[i][j] = 0;
			for (k = 0; k < MAXD; k++) {
				C.matrix[i][j] = (C.matrix[i][j] + A.matrix[i][k] * B.matrix[k][j]) % MOD;
			}
		}
	return C;
}

Array mul(const Array &A, const Matrix &B) {
	Array C;
	int i, j;
	for (i = 0; i < MAXD; i++) {
		C.array[i] = 0;
		for (j = 0; j < MAXD; j++)
			C.array[i] = (C.array[i] + A.array[j] * B.matrix[j][i]) % MOD;
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

int main() {
	int numOfCase;
	scanf("%d", &numOfCase);
	while (numOfCase--) {
		input();
		build_matrix();
		int T, n;
		scanf("%d", &T);
		while (T--) {
			int n;
			scanf("%d", &n);
			if (n < MAXD) {
				printf("%d\n", F.array[n] % MOD);
			} else {
				Matrix M = pow(E, n+1-MAXD);
				Array fn = mul(F, M);
				printf("%d\n", fn.array[MAXD-1] % MOD);
			}
		}
	}
return 0;
}

