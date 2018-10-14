/* Single Source Shortest Path */

#include<stdio.h>
#include<limits.h>
#include<conio.h>
#include "pheap.h"
#include "pedge.h"
#define INF INT_MAX
#define NIL 0
#define N 21

int n, E, parent[N], key[N], source;

int min(int i,int j)
{
	return (key[i]<key[j]);
}

void init(int n,int e)
{
	int i;
	edgeinit(n+1,e+e+1);
	heapinit(n+n+1,min);
	for(i=1;i<=n;i++)
		key[i]=INF, parent[i]=NIL, heapassign(i);
}

void read()
{
	int e,src,dst,wt,i,j;
	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&e);
	init(n,e);
	for(i=1;i<=e;i++)
	{
		scanf("%d%d%d",&src,&dst,&wt);
		insertedge(src,dst,wt);
	}
	scanf("%d",&source);
	key[source]=0, parent[source]=source, heapify();
}

void SSSPath()
{
	int dst,wt,next,i,src;
	while(!heapempty())
	{
		src=deleteroot(), setsource(src);
		while(getnextedge(&dst,&wt))
			if(wt+key[src]<key[dst])
				parent[dst]=src, key[dst] = key[src] + wt;
		heapify();
	}
}

void dfs(int i)
{
	if(i==parent[i])
	{
		printf("%d",i);
		return;
	}
	dfs(parent[i]);
	printf(" -> %d",i);
}

void output()
{
	int i;
	printf("\n");
	for(i=1;i<=n;i++)
	{
		if(i!=source)
		{
			dfs(i);
			printf(". COST: %d\n\n",key[i]);
		}
	}
}


void main()
{
	clrscr();
	read();
	SSSPath();
	output();
}