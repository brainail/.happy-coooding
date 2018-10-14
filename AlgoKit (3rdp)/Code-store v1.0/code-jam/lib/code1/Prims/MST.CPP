/* Prims Algorithm: Minimum Cost Spanning Tree */

#include<stdio.h>
#include<limits.h>

#define INF INT_MAX
#define NIL 0

#include "pheap.h"
#include "pedge.h"

int parent[20], key[20], n, source;

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
	freopen("prims.in","r",stdin);
	scanf("%d%d",&n,&e);
	init(n,e);
	for(i=1;i<=e;i++)
	{
		scanf("%d%d%d",&src,&dst,&wt);
		insertedge(src,dst,wt);
		insertedge(dst,src,wt);
	}
	scanf("%d",&source);
	key[source]=0, parent[source]=source ,heapify();
}

void MST_Prims()
{
	int dst,wt,next,i,src;
	while(!heapempty())
	{
		src=deleteroot();
		key[src]=NIL;
		setsource(src);
		while(getnextedge(&dst,&wt))
			if(wt<key[dst])
				parent[dst]=src, key[dst]=wt;
		heapify();
	}
}

void output()
{
	int i;
	for(i=1;i<=n;i++)
		if(parent[i]!=i)
			printf("%4d->%4d\n",parent[i],i);
}

void main()
{
	read();
	MST_Prims();
	output();
}
