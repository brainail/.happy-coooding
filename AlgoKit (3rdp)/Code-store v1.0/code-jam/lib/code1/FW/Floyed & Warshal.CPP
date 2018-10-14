#include<stdio.h>
#include<values.h>

#define N 100
#define INF MAXINT

int mat[N][N], path[N][N], n, e;

void initMat()
{
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			mat[i][j] = INF;
}

void initPath()
{
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(mat[i][j]!=INF)
				path[i][j] = j;
			else
				path[i][j] = 0;
}

void floyd_warshall()
{
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(mat[i][k]!=INF && mat[k][j]!=INF)
					if(mat[i][k]+mat[k][j] < mat[i][j])
						mat[i][j] = mat[i][k] + mat[k][j], path[i][j] = path[i][k];
}

void showPath(int i, int j)
{
	if(i==j)
	{
		printf("->%d", i);
		return;
	}
	printf("->%d", i);
	showPath(path[i][j], j);
}

void main()
{
	freopen("in.txt", "r", stdin);
	while(scanf("%d%d", &n, &e) && n && e)
	{
		initMat();
		for(int i, j, c, k=0; k<e; k++)
		{
			scanf("%d%d%d", &i, &j, &c);
			mat[i][j] = c;
		}
		initPath();
		floyd_warshall();
		for(i=1; i<=n; i++)
		{
			for(j=1; j<=n; j++)
				if(path[i][j])
				{
					printf("%d", i);
					showPath(path[i][j], j);
					printf("\n");
				}
				printf("\n");
		}
	}
}
