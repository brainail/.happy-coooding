#include<stdio.h>
#include<conio.h>
#include<limits.h>
#define NIL 0
#define INF MAX_INT
#define N 20

int node[N][N],n,e;

initialization()
{
   int i,src,dst,wt;
   for(i=1;i<=e;i++)
   {
      scanf("%d%d%d",&src,&dst,&wt);
      node[src][dst]=wt;
   }
}

input()
{
   //int
   freopen("Bell-1.in","r",stdin);
   scanf("%d%d",&n,&e);
   initialization();
}
main()
{
   input();
   bellmanford();
}