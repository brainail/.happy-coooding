/* Max Flow */

/* @begin_of_source_code */
/* @judge_id: 6401 10330 C++ "Split Vertex" */

# include <stdio.h>
# include <values.h>

# define MAXVERTICES 202
# define Q MAXVERTICES+1

# define min(a,b) (((a)<(b))? (a):(b))

int n;
int c[MAXVERTICES][MAXVERTICES];
int f[MAXVERTICES][MAXVERTICES];
int cf[MAXVERTICES][MAXVERTICES];

int setCapacity(void)
{
  /* get input and make the graph */
  /* 0 : source   ,    n : sink */
  int m,i,j,k,s,t;
  if(scanf("%d",&n)!=1) return 0;
  for(i=0;i<=2*n+1;i++)
    for(j=0;j<=2*n+1;j++)
      c[i][j]=0;
  for(i=1;i<=n;i++)
    scanf("%d",&c[i][i+n]);
  scanf("%d",&m);
  while(m--){
    scanf("%d%d%d",&i,&j,&k);
    c[i+n][j]=k;
  }
  scanf("%d%d",&s,&t);
  while(s--){
    scanf("%d",&j);
    c[0][j]=MAXINT;
  }
  while(t--){
    scanf("%d",&i);
    c[i+n][2*n+1]=MAXINT;
  }
  n=2*n+1;
  return 1;
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
  if(!setCapacity()) return -1;
  initialize();
  while(augment());
  for(totflow=0,i=0;i<=n;i++)
    totflow+=f[0][i];
  return totflow;
}

int main(void)
{
  int tot;
  while(1){
    tot=maxFlow();
    if(tot==-1) break;
    printf("%d\n",tot);
  }
  return 0;
}

/* @end_of_source_code */
