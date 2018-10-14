/* Job Scheduling of n jobs with deadlines di and 
   penalty/profit pi. If pi is profit late jobs 
   give 0 profit. if pi is penalty only late jobs
   have penalties. Time complexity = O(n*lgn) */

# include <stdio.h>
# include <stdlib.h>

# define MAXJOBS 1000
# define min(a,b) (((a)<(b))? (a):(b))

typedef struct{
  int d,p,alpha;
  /* job done in [alpha-1,alpha] */
}Job;

int p[MAXJOBS+1],rank[MAXJOBS+1],a[MAXJOBS+1];

void MakeSet(int x)
{
  p[x]=x;
  rank[x]=0;
}

int FindSet(int x)
{
  if(x!=p[x]) p[x]=FindSet(p[x]);
  return p[x];
}

void Union(int u,int v)
{
  int x,y;
  x=FindSet(u);
  y=FindSet(v);
  if(rank[x]>rank[y])
    p[y]=x;
  else{
    p[x]=y;
    if(rank[x]==rank[y])
      rank[y]++;
  }
}
  
int cmp(const void *a,const void *b)
{
  Job u,v;
  u=*(Job *)a;
  v=*(Job *)b;
  return v.p-u.p;
}

/* Jobs are q[1],q[2],....,q[n] 
   If job i is late q[i].alpha==0 */

void Schedule(Job q[],int n)
{
  int i,j,k,l;
  qsort(q+1,n,sizeof(Job),cmp);
  MakeSet(0);
  a[0]=0;
  for(i=1;i<=n;i++){
    MakeSet(i);
    a[i]=i;
    q[i].alpha=0;
  }
  q[1].alpha=min(q[1].d,n);
  Union(q[1].alpha-1,q[1].alpha);
  j=FindSet(q[1].alpha);
  a[j]=a[q[1].alpha-1];
  for(i=2;i<=n;i++){
    j=FindSet(min(q[i].d,n));
    if(!a[j]) continue;
    q[i].alpha=a[j];
    k=FindSet(a[j]-1);
    Union(j,k);
    l=FindSet(j);
    a[l]=a[k];
  }
}

int main(void)
{
  int n;
  Job q[MAXJOBS+1];
  int i;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
    scanf("%d%d",&q[i].d,&q[i].p);
  Schedule(q,n);
  return 0;
}
  