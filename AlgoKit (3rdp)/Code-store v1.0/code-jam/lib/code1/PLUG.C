/* "A plug for UNIX" : Network Flow */
/* @begin_of_source_code */
/* @judge_id: 6401 753 C */
# include <stdio.h>
# include <string.h>
# define SIZE 100
# define G 3*SIZE+2
# define Q G+1
# define M 25
int p,q,r;
char pn[SIZE][M],qn[SIZE][2][M],rn[SIZE][2][M];
int c[G][G],cf[G][G],f[G][G];
int t;

int bfs(int src)
{
  int i,j;
  int cost[G],par[G];
  int que[Q],rear,front;
  for(j=0;j<=t;j++)
    cost[j]=-1;
  cost[src]=0;
  par[src]=-1;
  rear=front=0;
  que[rear]=src;
  rear++;
  if(rear==Q) rear=0;
  while(rear!=front){
    i=que[front];
    front++;
    if(front==Q) front=0;
    if(i==t) break;
    for(j=0;j<=t;j++)
      if(cf[i][j] && cost[j]==-1){
	cost[j]=cost[i]+1;
	par[j]=i;
	que[rear]=j;
	rear++;
	if(rear==Q) rear=0;
      }
  }
  if(i!=t) return 0;
  while(par[i]!=-1){
    if(c[par[i]][i]){
      f[par[i]][i]=1;
      cf[par[i]][i]=0;
      cf[i][par[i]]=1;
    }
    else{
      f[i][par[i]]=0;
      cf[par[i]][i]=0;
      cf[i][par[i]]=1;
    }
    i=par[i];
  }
  return 1;
}

int main(void)
{
  int T;
  int i,j;
  scanf("%d",&T);
  while(T--){
    scanf("%d",&p);
    for(i=0;i<p;i++)
      scanf("%s",pn[i]);
    scanf("%d",&q);
    for(i=0;i<q;i++)
      scanf("%s%s",&qn[i][0],&qn[i][1]);
    scanf("%d",&r);
    for(i=0;i<r;i++)
      scanf("%s%s",&rn[i][0],&rn[i][1]);
    t=p+q+r+1;
    for(i=0;i<=t;i++)
      for(j=0;j<=t;j++)
	c[i][j]=f[i][j]=cf[i][j]=0;
    for(j=1;j<=q;j++)
      c[0][j]=cf[0][j]=1;
    for(i=0;i<q;i++){
      for(j=0;j<r;j++)
	if(strcmp(qn[i][1],rn[j][0])==0)
	  c[i+1][j+q+1]=cf[i+1][j+q+1]=1;
      for(j=0;j<p;j++)
	if(strcmp(qn[i][1],pn[j])==0)
	  c[i+1][j+q+r+1]=cf[i+1][j+q+r+1]=1;
    }
    for(i=0;i<r;i++){
      for(j=0;j<r;j++)
	if(strcmp(rn[i][1],rn[j][0])==0)
	  c[i+q+1][j+q+1]=cf[i+q+1][j+q+1]=1;
      for(j=0;j<p;j++)
	if(strcmp(rn[i][1],pn[j])==0)
	  c[i+q+1][j+q+r+1]=cf[i+q+1][j+q+r+1]=1;
    }
    for(j=q+r+1;j<t;j++)
      c[j][t]=cf[j][t]=1;
    while(bfs(0))
      ;
    for(j=0,i=1;i<=q;i++)
      if(f[0][i])
	j++;
    printf("%d\n",q-j);
    if(T) printf("\n");
  }
  return 0;
}
/* @end_of_source_code */
