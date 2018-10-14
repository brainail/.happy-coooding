#include<stdio.h>
#include<values.h>

#define N 30

long mat[N][N], D[N], order[N][N];

void init()
{
	for(long i=0; i<N; i++)
		for(long j=0; j<N; j++)
			if(i==j)
				mat[i][j] = 0;
			else
				mat[i][j] = MAXLONG;
}

long MCM(long n)
{
	for(long l=2; l<=n; l++)
		for(long j, i=1; i<=n-l+1; i++)
		{
			j = i + l - 1;
			for(long q, k=i; k<j; k++)
			{
				q = mat[i][k] + mat[k+1][j] + D[i-1] * D[k] * D[j];
				if(q < mat[i][j])
					mat[i][j] = q, order[i][j] = k;
			}
		}
	return mat[1][n];
}

void showOrder(long i, long j)
{
	if(i==j)
	{
		printf("A%ld", i);
		return;
	}
	int k = order[i][j];
	printf("(");
	showOrder(i, k);
	printf(" x ");
	showOrder(k+1, j);
	printf(")");
}

void main()
{
	freopen("in.txt", "r", stdin);
	long c=0, n, i, j, k;
	while(scanf("%ld", &n) && n)
	{
		for(i=0, k=0; k<n; k++)
			scanf("%ld%ld", &D[i++], &j);
		D[i] = j, init(), printf("%d: ", MCM(n));
		showOrder(1, n);
		printf("\n");
	}
}
