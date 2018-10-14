#include<stdio.h>
#include<conio.h>

#define notvisited 0
#define visiting 1
#define visited 2
#define maxnode 50
#define adjacent 1
#define notadjacent 0

#include"pedge.h"


struct edge
 {
	int u, v;
 }stack[maxnode+1];

int top, n,e,time, point[maxnode+1], root, com, co=0, ap[maxnode+1], co1=0;
int adj[maxnode+1][maxnode+1], discover[maxnode+1], finish[maxnode+1], parent[maxnode+1], status[maxnode+1];

void printart(int r)
{
	printf("Articulation points ");
	for(int i=1; i<=n; i++)
		{
			if(point[i]!=0)
				{
					if(i==r)
					{
					if(point[i]>1)
						printf("%d ", i);
					}

					else
					printf ("%d ", i);
				}
		}

}
edge pop(void)
{
	return stack[top--];
}

void getcomp(int u, int v)
{
	edge e, g[50];
	int i=0;

	while(1)
		{
			e=pop();
			g[++i]=e;
			if(e.u==u && e.v==v)
				break;
			if(e.u==v && e.v==u)
				break;
		}
	if(i>1)
		{
			printf("Component %d\n", ++com);
			while(i>0)
				{
					printf("%2d%2d\n", g[i].u, g[i].v);
					i--;
				}
		}
	else
		{
			if(g[1].u==root && point[root]!=1)
				{
					point[root]=1;
				}

			printf("Bridge %d\n%d->%d\n", ++co, g[1].u, g[1].v);
		}
}
void push(edge e)
{
	stack[++top]=e;
}

int min(int a, int b)
{
	return (a<b ? a:b);
}

void articulation(int u)
{
	int v;
	edge e;
	int x;
	status[u]=visiting;
	discover[u]=finish[u]=++time;
	//for(v=1; v<=n; v++)
		//if(adj[u][v]==adjacent)
	x=NodeHead[u];
	while(x!=NIL)
		{
			v=EdgeList[x].dst;
			for(v=1; v<=n; v++){
			if(parent[u]!=v && discover[v]<discover[u])
				{
					e.u=u;
					e.v=v;
					push(e);
				}
			if(status[v]==notvisited)
				{
					parent[v]=u;
					articulation(v);
					if(finish[v]>=discover[u])
						{
							point[u]+=1;
							getcomp(u, v);
						}
					finish[u]=min(finish[u], finish[v]);
				}
			else
				if(parent[u]!=v)
		x=EdgeList[x].next;			finish[u]=min(finish[u], discover[v]);
		}}
	status[u]=visited;
}
void read(void)
{
 int i,src,dst,nd[20],ttr=0;;
 clrscr();
 freopen("topo.in","r",stdin);
 scanf("%d%d",&n,&e);
 for(i=0;i<=n;i++)
 {
    discover[i]=finish[i]=NIL;
    nd[i]=i;
 }
 EdgeInit(n);
 for(i=1;i<=e;i++)
 {
   scanf("%d%d",&src,&dst);
   InsertEdge(src,dst,NIL,i);
 }
}

void main(void)
{
	clrscr();
	freopen("arti.in", "r", stdin);
	int i, j;
	read();
	root=1 ;
	printf("\n");
	articulation(root);
	printart(root);
}