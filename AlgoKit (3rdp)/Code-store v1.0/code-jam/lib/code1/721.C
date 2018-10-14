/* dijkstra with heap */

/* @begin_of_source_code */
/* @judge_id: 6401 721 C++ */

# include <stdio.h>
# include <stdlib.h>
# include <values.h>

# define MAX 1000000

typedef struct{
  int u,v,c;
}Edge;

int cmp1(const void *a,const void *b)
{
  Edge x=*(Edge *)a;
  Edge y=*(Edge *)b;
  if(x.u!=y.u) return x.u-y.u;
  return x.v-y.v;
}

int cmp2(const void *a,const void *b)
{
  Edge x=*(Edge *)a;
  Edge y=*(Edge *)b;
  if(x.v!=y.v) return x.v-y.v;
  return x.u-y.u;
}

int n,m;
int start[MAX+1];

int d[MAX+1],p[MAX+1];
int a[MAX+1],h;

void siftdown(int i)
{
  int l,r,smallest,t;
  while(1){
    l=2*i;
    r=2*i+1;
    if(l<=h && d[a[l]]<d[a[i]]) smallest=l;
    else smallest=i;
    if(r<=h && d[a[r]]<d[a[smallest]]) smallest=r;
    if(i==smallest) break;
    t=a[i];
    a[i]=a[smallest];
    a[smallest]=t;
    p[a[smallest]]=smallest;
    p[a[i]]=i;
    i=smallest;
  }
}

void siftup(int i)
{
  int t;
  while(i>1 && d[a[i]]<d[a[i/2]]){
    t=a[i];
    a[i]=a[i/2];
    a[i/2]=t;
    p[a[i]]=i;
    p[a[i/2]]=i/2;
    i/=2;
  }
}

int extractmin(void)
{
  int mini=a[1];
  a[1]=a[h--];
  p[a[1]]=1;
  siftdown(1);
  return mini;
}

void adjust(int i)
{
  siftup(p[i]);
}

Edge list[MAX+1];

int main(void)
{
  int T;
  int i,j,k,l,sum;
/*  freopen("721.in","r",stdin); */
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++){
      scanf("%d%d%d",&list[i].u,&list[i].v,&list[i].c);
      list[i].u--;
      list[i].v--;
    }
    qsort(list,m,sizeof(Edge),cmp1);
    start[0]=0;
    for(i=1,j=0;i<m;i++)
      if(list[i].u!=j)
        start[++j]=i;
    start[++j]=m;
    for(i=0;i<n;i++){
      d[i]=MAXINT;
      a[i+1]=i;
      p[i]=i+1;
    }
    d[0]=0;
    for(h=n,i=n/2;i>0;i--)
      siftdown(i);
    for(k=0;k<n;k++){
      i=extractmin();
      for(l=start[i];l<start[i+1];l++){
        j=list[l].v;
        if(d[j]>d[i]+list[l].c){
          d[j]=d[i]+list[l].c;
          adjust(j);
        }
      }
    }
    sum=0;
    for(i=0;i<n;i++)
      sum+=d[i];
    qsort(list,m,sizeof(Edge),cmp2);
    start[0]=0;
    for(i=1,j=0;i<m;i++)
      if(list[i].v!=j)
	start[++j]=i;
    start[++j]=m;
    for(i=0;i<n;i++){
      d[i]=MAXINT;
      a[i+1]=i;
      p[i]=i+1;
    }
    d[0]=0;
    for(h=n,i=n/2;i>0;i--)
      siftdown(i);
    for(k=0;k<n;k++){
      i=extractmin();
      for(l=start[i];l<start[i+1];l++){
        j=list[l].u;
        if(d[j]>d[i]+list[l].c){
          d[j]=d[i]+list[l].c;
          adjust(j);
        }
      }
    }
    for(i=0;i<n;i++)
      sum+=d[i];
    printf("%d\n",sum);
  }
  return 0;
}

/* @end_of_source_code */
