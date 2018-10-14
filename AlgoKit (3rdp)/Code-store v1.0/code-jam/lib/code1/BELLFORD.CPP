/*bellmanford algorithm*/

#include<limits.h>
#include<stdio.h>
#include<conio.h>

#define INF INT_MAX
#define NIL 0


int Key[20],n,source,e;
struct E{
		  int src,dst,wt;
		} Edge[50];

int Min(int i,int j)
{
	return (Key[i]<Key[j]);
}

#include"pheap.h"
#include"pedge.h"

int Parant[20];

void Initialization(int n)
{
	int i;
	EdgeInit(n);
	HeapInit(n);
	for(i=1;i<=n;i++)
	{
		Key[i]=INF;
		Parant[i]=NIL;
	}
}

void Input(void)
{
	int s,d,w,i,j;

	freopen("bellman.in","r",stdin);
	scanf("%d%d",&n,&e);
	Initialization(n);

	for(i=1;i<=e;i++)
	{
		scanf("%d%d%d",&s,&d,&w);
		Edge[i].src=s;
		Edge[i].dst=d;
		Edge[i].wt=w;
	}
	scanf("%d",&source);
	Key[source]=0;
	Parant[source]=source;
}

int  BF_alg(void)
{
	int i,j,src,dst,wt;
	for(i=1;i<=n-1;i++)
	{
		for(j=1;j<=e;j++)
		{
			src=Edge[j].src,dst=Edge[j].dst,wt=Edge[j].wt;
			if(Key[dst]>Key[src]+wt)
			{
				Key[dst]=Key[src]+wt;
				Parant[dst]=src;
			}
		}
	}
	for(j=1;j<=e;j++)
	{
		src=Edge[j].src;
		dst=Edge[j].dst;
		wt=Edge[j].wt;
		if(Key[dst]>Key[src]+wt)
			return 0;
	}
	return 1;
}

void Output(void)
{
	int i;
	clrscr();
	for(i=1;i<=n;i++)
		  printf("1 ->%4d:%4d, \n",i,Key[i]);


}

void main()
{
	Input();
	if(BF_alg)
	{
		BF_alg();
		Output();
	}
	else
		printf("No Path exits");
}