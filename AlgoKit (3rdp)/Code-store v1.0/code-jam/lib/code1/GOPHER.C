/* Maximum Bipartite Matching */

# include <stdio.h>
# include <math.h>

# define s(a) ((a)*(a))
# define SIZE 200
# define Q SIZE+1

typedef struct{
  double x,y;
}Point;

int t,match[SIZE];
int d[SIZE][SIZE];

double dist(Point a,Point b)
{
  return sqrt(s(a.x-b.x)+s(a.y-b.y));
}

void MaximumBipartiteMatching(void)
{
  int i,j,k;
  int level[SIZE],p[SIZE];
  int q[Q],r,f;
  int last;
  for(i=0;i<t;i++)
    if(match[i]==-1){
      for(j=0;j<=t;j++){
	  level[j]=0;
	  p[j]=-1;
      }
      last=-1;
      level[i]=1;
      r=f=0;
      q[r]=i;
      r++;
      if(r==Q) r=0;
      while(r!=f){
	  j=q[f];
	  f++;
	  if(f==Q) f=0;
	  if(level[j]%2){
	    for(k=0;k<t;k++)
	      if(d[j][k] && level[k]==0){
	        if(match[k]==-1){
		    level[k]=level[j]+1;
		    p[k]=j;
		    last=k;
		    break;
	        }
	        else{
		    level[k]=level[j]+1;
		    p[k]=j;
		    q[r]=k;
		    r++;
		    if(r==Q) r=0;
	        }
	      }
	  }
	  else{
	    k=match[j];
	    level[k]=level[j]+1;
	    p[k]=j;
	    q[r]=k;
	    r++;
	    if(r==Q) r=0;
	  }
	  if(last!=-1) break;
      }
      while(last!=-1){
	  match[last]=p[last];
	  match[p[last]]=last;
	  last=p[p[last]];
      }
    }
}

int main(void)
{
  int n,m,s,v;
  Point g[SIZE/2],h[SIZE/2];
  int i,j;
  while(scanf("%d%d%d%d",&n,&m,&s,&v)==4){
    for(i=0;i<n;i++)
      scanf("%lf%lf",&g[i].x,&g[i].y);
    for(i=0;i<m;i++)
      scanf("%lf%lf",&h[i].x,&h[i].y);
    t=m+n;
    for(i=0;i<t;i++){
      match[i]=-1;
      for(j=0;j<t;j++)
	  d[i][j]=0;
    }
    for(i=0;i<n;i++)
      for(j=0;j<m;j++)
	  if(dist(g[i],h[j])<=s*v)
	    d[i][n+j]=d[n+j][i]=1;
    MaximumBipartiteMatching();
    j=0;
    for(i=0;i<n;i++)
      if(match[i]==-1)
	  j++;
    printf("%d\n",j);
  }
  return 0;
}
