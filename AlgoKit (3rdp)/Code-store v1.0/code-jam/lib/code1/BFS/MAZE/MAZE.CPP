#include<stdio.h>
#include<conio.h>
#include<values.h>

#define N 100
#define MAX MAXINT

int mat[N][N], Q[N][3], cost[N][N], front = -1, rear = -1;
int m, n, sc, sr, p, nr, nc, r, c, leaf, i, j, res[10][10];
int R[4] = {0, -1, 0, 1};
int C[4] = {-1, 0, 1, 0};

void nQ(int r, int c, int p)
{
	Q[++rear][0] = r, Q[rear][1] = c, Q[rear][2] = p;
}

void dQ(int *r, int *c, int *p)
{
	*r = Q[++front][0], *c = Q[front][1], *p = front;
}

void bfs(int sr, int sc, int p)
{
	nQ(sr, sc, p);
	do{
		dQ(&r, &c, &p);
		for(int i=0; i<4; i++)
		{
			nr = r + R[i], nc = c + C[i];
			if(mat[nr][nc]==1)
			{
				if(cost[nr][nc]>cost[r][c]+1)
					cost[nr][nc]=cost[r][c]+1, nQ(nr, nc, p);
			}
		}
	} while (rear!=front);
	leaf = p;
}

void show()
{
	for(int i=0; i<=m; i++)
	{
		for(int j=0; j<=n; j++)
		{
			if(res[i][j])
				printf("X");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void dfs(int leaf)
{
	if(Q[leaf][2]==-1)
	{
		res[Q[leaf][0]][Q[leaf][1]] = 1;
		return;
	}
	dfs(Q[leaf][2]);
	res[Q[leaf][0]][Q[leaf][1]] = 1;
}

void main()
{
	clrscr();
	char ch;
	freopen("maze.txt", "r", stdin);
	scanf("%d%d", &m, &n);
	getchar();
	for(i=0; i<m; i++)
	{
		for(j=0; j<n; j++)
		{
			cost[i][j] = MAX;
			scanf("%c", &ch);
			if(ch=='#')
				mat[i][j] = 0;
			else if(ch=='.')
				mat[i][j] = 1;
			else if(ch=='s')
				mat[i][j] = 2, sc = j, sr = i;
			else
				mat[i][j] = 3, res[i][j] = 1;
		}
		getchar();
	}
	bfs(sr, sc, -1);
	dfs(leaf);
	show();
}

