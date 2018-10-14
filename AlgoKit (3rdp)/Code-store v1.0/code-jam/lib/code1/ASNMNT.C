/* Assignment Problem */

# include <stdio.h>
# define SIZE 5

void matching(int c[2*SIZE][2*SIZE],int n,int m[2*SIZE])
{
  int qsize=n+1;
  int q[2*SIZE+1],rear,front;
  int par[2*SIZE],level[2*SIZE];
  int i,j,k,last;
  for(i=0;i<n;i++)
    m[i]=-1;
  for(k=0;k<n;k++)
    if(m[k]==-1){
      last=-1;
      for(i=0;i<n;i++){
	level[i]=0;
	par[i]=-1;
      }
      rear=front=0;
      level[k]=1;
      q[rear++]=k;
      if(rear==qsize) rear=0;
      while(rear!=front){
	if(last!=-1) break;
	i=q[front++];
	if(front==qsize) front=0;
	if(level[i]%2){
	  for(j=0;j<n;j++)
	    if(c[i][j] && level[j]==0){
	      level[j]=level[i]+1;
	      par[j]=i;
	      if(m[j]==-1){
		last=j;
		break;
	      }
	      else{
		q[rear++]=j;
		if(rear==qsize) rear=0;
	      }
	    }
	}
	else{
	  j=m[i];
	  level[j]=level[i]+1;
	  par[j]=i;
	  q[rear++]=j;
	  if(rear==qsize) rear=0;
	}
      }
      while(last!=-1){
	m[last]=par[last];
	m[par[last]]=last;
	last=par[par[last]];
      }
    }
}

int isperfect(int m[],int n)
{
  int i;
  for(i=0;i<n;i++)
    if(m[i]==-1)
      return 0;
  return 1;
}

void dfs(int k,int i,int mark[2][SIZE],int e[SIZE][SIZE],int n,int m[],int depth)
{
  int j;
  if(depth) mark[k][i]=1;
  if(k==0){
    for(j=0;j<n;j++)
      if(e[i][j]==0 && m[i]!=j+n){
	mark[k][i]=1;
	if(mark[1][j]==0)
	  dfs(1,j,mark,e,n,m,depth+1);
      }
  }
  else{
    for(j=0;j<n;j++)
      if(e[j][i]==0 && m[i+n]==j){
	mark[k][i]=1;
	if(mark[0][j]==0)
	  dfs(0,j,mark,e,n,m,depth+1);
      }
  }
}

void OptimalAssignment(int w[SIZE][SIZE],int n,int m[])
{
  int u[SIZE],v[SIZE];
  int e[SIZE][SIZE],c[2*SIZE][2*SIZE];
  int mark[2][SIZE];
  int i,j,k,eta;
  for(i=0;i<n;i++){
    u[i]=v[i]=0;
    for(j=0;j<n;j++)
      if(w[i][j]>u[i])
	u[i]=w[i][j];
  }
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      e[i][j]=u[i]+v[j]-w[i][j];
  for(i=0;i<2*n;i++)
    for(j=0;j<2*n;j++)
      c[i][j]=0;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(e[i][j]==0)
	c[i][n+j]=c[n+j][i]=1;
  matching(c,2*n,m);
  while(!isperfect(m,2*n)){
    for(i=0;i<n;i++)
      mark[0][i]=mark[1][i]=0;
    for(i=0;i<n;i++)
      if(m[i]==-1 && mark[0][i]==0)
	dfs(0,i,mark,e,n,m,0);
    eta=-1;
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	if(mark[0][i] && mark[1][j]==0)
	  if(eta==-1 || eta>u[i]+v[j]-w[i][j])
	    eta=u[i]+v[j]-w[i][j];
    for(i=0;i<n;i++){
      if(mark[0][i])
	u[i]-=eta;
      if(mark[1][i])
	v[i]+=eta;
    }
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	e[i][j]=u[i]+v[j]-w[i][j];
    for(i=0;i<2*n;i++)
      for(j=0;j<2*n;j++)
	c[i][j]=0;
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	if(e[i][j]==0)
	  c[i][n+j]=c[n+j][i]=1;
    matching(c,2*n,m);
  }
}

int main(void)
{
  int n=5;
  int w[SIZE][SIZE]={{4,1,6,2,3},
		     {5,0,3,7,6},
		     {2,3,4,5,8},
		     {3,4,6,3,4},
		     {4,6,5,8,6}};
  int m[2*SIZE];
  int i,total;
  OptimalAssignment(w,n,m);
  total=0;
  for(i=0;i<n;i++)
    total+=w[i][m[i]-n];
  printf("%d\n",total);
  return 0;
}
