/*dsf total cycle*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

#include "pedge.h"

int n,e,d[20],f[20],t,cir,circ,cnd[20];

int SortFunction(const void *a,const void *b)
{
   int i=*((int *)a);
   int j=*((int *)b);
   if(f[i]<f[j]) return 1;
   if(f[i]>f[j]) return -1;
   return 0;
}

void Topo(int node)
{
  int i,v;
  static int j;
  d[node]=++t;
  cnd[j++]=node;
  printf(" %d",node);
  i=NodeHead[node];
  while(i!=NIL)
  {
    v=EdgeList[i].dst;
    if(d[v]==0)
	    {
	      circ=0;
	      Topo(v);
	    }
    i=EdgeList[i].next;
  }
  if(circ==0) cir+=1;
  f[node]=++t;
  circ+=1;
}
main()
{
 int i,src,dst,nd[20],ttr=0;;
 clrscr();
 freopen("dfs.in","r",stdin);
 scanf("%d%d",&n,&e);
 for(i=0;i<=n;i++)
 {
    d[i]=f[i]=NIL;
    nd[i]=i;
 }
 EdgeInit(n);
 for(i=1;i<=2*e;i+=2)
 {
   scanf("%d%d",&src,&dst);
   InsertEdge(src,dst,NIL,i);
   InsertEdge(dst,src,NIL,i+1);
 }
 t=0;
 for(i=1;i<=n;i++)
 {
   if(d[i]==0) {ttr+=1;printf("\nTree-%d :: ",ttr);Topo(i);}
 }
 qsort((void *) (nd+1),n,sizeof(nd[0]),SortFunction);
 for(i=1;i<=n;i++)
 {
   printf("\n%d\\",*(nd+i));
 }
 fclose(stdin);
 printf("\nTotal cycle=%d",cir);
 printf("\nOK");
}