/* STL priority queue */

/* @begin_of_source_code */
/* @judge_id: 6401 10259 C++ "Testing STL priority_queue" */

# include <stdio.h>
# include <queue>

# define MAX 100

int n,c[MAX][MAX];

struct Pair{
  int i,j;
};

priority_queue<Pair> q;

bool operator<(const Pair &a,const Pair &b)
{
  return c[a.i][a.j]>c[b.i][b.j];
}

int main(void)
{
  int T;
  int m,p[MAX][MAX];
  int f[MAX][MAX];
  Pair s,t;
  int di[]={0,-1,0,1};
  int dj[]={-1,0,1,0};
  int i,j,k,l,ti,tj,maxp;
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
      for(j=0;j<n;j++){
        scanf("%d",&c[i][j]);
        p[i][j]=0;
        f[i][j]=0;
      }
    p[0][0]=c[0][0];
    s.i=s.j=0;
    q.push(s);
    f[0][0]=1;
    while(q.size()){
      s=q.top();
      q.pop();
      i=s.i;
      j=s.j;
      f[i][j]=0;
      for(l=0;l<4;l++)
        for(k=1;k<=m;k++){
          ti=i+k*di[l];
          tj=j+k*dj[l];
          if(ti<0 || ti>=n || tj<0 || tj>=n) break;
          if(c[ti][tj]>c[i][j] && p[ti][tj]<p[i][j]+c[ti][tj]){
            t.i=ti;
            t.j=tj;
            p[ti][tj]=p[i][j]+c[ti][tj];
            if(!f[ti][tj]){
              q.push(t);
              f[ti][tj]=1;
            }
	  }
	}
    }
    for(maxp=0,i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(maxp<p[i][j])
          maxp=p[i][j];
    printf("%d\n",maxp);
    if(T) printf("\n");
  }
  return 0;
}

/* @end_of_source_code */
