#include<stdio.h>
#define N 100

int n, e, cost[N][N], dst, visit[N], found, w;

void init()
{
	for(int i=1; i<N; i++)
	{
		for(int j=1; j<N; j++)
			cost[i][j] = 0;
		visit[i] = 0;
	}
	found = 0, w = 0;
}

void dfs(int src)
{
	visit[src] = 1;
	if(src==dst)
	{
		found = w;
		return;
	}
	for(int i=1; i<=n; i++)
		if(src!=i && cost[src][i] && !visit[i] && !found)
			w+=cost[src][i], dfs(i), w-=cost[src][i];
}

void main()
{
	int wt, u, v;
	init();
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &e);
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d%d", &u, &v, &wt);
		cost[u][v] = cost[v][u] = wt;
	}
	dst = 4;
	dfs(1);
	if(found)
		printf("There's a way, Cost is %d.\n", found);
	else
		printf("There's  no way!\n");
}