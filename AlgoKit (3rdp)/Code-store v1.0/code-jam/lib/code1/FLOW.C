/* Max Flow */

# include <stdio.h>
# include <values.h>

# define MAXVERTICES 202
# define Q MAXVERTICES+1

# define min(a,b) (((a)<(b))? (a):(b))

int n;
int c[MAXVERTICES][MAXVERTICES];
int f[MAXVERTICES][MAXVERTICES];
int cf[MAXVERTICES][MAXVERTICES];

void setCapacity(void)
{
  /* get input and make the graph */
  /* 0 : source   ,    n : sink */

}

void initialize(void)
{
  int i,j;
  for(i=0;i<=n;i++)
    for(j=0;j<=n;j++){
      f[i][j]=0;
      cf[i][j]=c[i][j];
    }
}

int augment(void)
{
  int q[Q],rear,front;
  int cost[MAXVERTICES],p[MAXVERTICES];
  int cfp,i,j;
  for(i=0;i<=n;i++)
    cost[i]=p[i]=-1;
  cost[0]=0;
  rear=front=0;
  q[rear++]=0;
  while(rear!=front){
    i=q[front++];
    if(front==Q) front=0;
    if(i==n) break;
    for(j=0;j<=n;j++)
      if(cf[i][j]>0 && cost[j]==-1){
        cost[j]=cost[i]+1;
        p[j]=i;
        q[rear++]=j;
        if(rear==Q) rear=0;
      }
  }
  if(cost[n]==-1) return 0;
  cfp=MAXINT;
  i=n;
  while(i){
    cfp=min(cfp,cf[p[i]][i]);
    i=p[i];
  }
  i=n;
  while(i){
    f[p[i]][i]+=cfp;
    f[i][p[i]]=-f[p[i]][i];
    cf[p[i]][i]-=cfp;
    cf[i][p[i]]+=cfp;
    i=p[i];
  }
  return 1;
}

int maxFlow(void)
{
  int i,totflow;
  setCapacity();
  initialize();
  while(augment());
  for(totflow=0,i=0;i<=n;i++)
    totflow+=f[0][i];
  return totflow;
}

