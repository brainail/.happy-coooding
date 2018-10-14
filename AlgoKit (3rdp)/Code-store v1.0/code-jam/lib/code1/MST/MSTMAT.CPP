#include<stdio.h>
#include<conio.h>
#include<values.h>

#define N 100
#define INF MAXINT
#define NIL 0

int source, n, cost[N][N], parent[N];
struct node
{
	int n, c;
} a[N], k;

void reset(int n)
{
	for(int i=1; i<=n; i++)
	{
		parent[i] = NIL, a[i].n = i, a[i].c = INF;
		for(int j=1; j<=n; j++)
			cost[i][j] = NIL;
	}
}

void read()
{
	int j, k, c, e;
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &e);
	reset(n);
	for(int i=1; i<=e; i++)
	{
		scanf("%d%d%d", &j, &k, &c);
		cost[j][k] = c, cost[k][j] = c;
	}
	scanf("%d", &source);
	parent[source] = source;
	a[source].c = NIL;
}

void sort(int nd)
{
	for(int i=nd; i<n; i++)
		for(int j=i+1; j<=n; j++)
			if(a[i].c > a[j].c)
				k = a[i], a[i] = a[j], a[j] = k;
}

void mst()
{
	for(int nd=1, src; nd<n; nd++)
	{
		sort(nd), src = a[nd].n, a[nd].c = NIL;
		for(int i=1, j; i<=n; i++)
			if(cost[src][i] != NIL)
				for(j=1; a[j].n != i; j++);
					if(cost[src][i] < a[j].c)
						parent[i] = src, a[j].c = cost[src][i];
	}
}

void out()
{
	for(int i=1; i<=n; i++)
		if(parent[i]!=i)
			printf("%4d -> %4d\n", parent[i], i);
}

void main()
{
	clrscr();
	read();
	mst();
	out();
}