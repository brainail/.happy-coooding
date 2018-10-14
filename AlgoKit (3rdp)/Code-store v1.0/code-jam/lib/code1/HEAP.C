/* Heap operation with siftup and siftdown */

# include <stdio.h>

# define MAX 14000

int v[MAX+1],p[MAX+1];
int a[MAX+1],h;

void siftdown(int i)
{
  int l,r,largest,t;
  while(1){
    l=2*i;
    r=2*i+1;
    if(l<=h && v[a[l]]>v[a[i]]) largest=l;
    else largest=i;
    if(r<=h && v[a[r]]>v[a[largest]]) largest=r;
    if(i==largest) break;
    t=a[i];
    a[i]=a[largest];
    a[largest]=t;
    p[a[largest]]=largest;
    p[a[i]]=i;
    i=largest;
  }
}

void siftup(int i)
{
  int t;
  while(i>1 && v[a[i]]>v[a[i/2]]){
    t=a[i];
    a[i]=a[i/2];
    a[i/2]=t;
    p[a[i]]=i;
    p[a[i/2]]=i/2;
    i/=2;
  }
}

int main(void)
{
  int m;
  int x,i;
  h=0;
# ifndef ONLINE_JUDGE
  freopen("1126.in","r",stdin);
  freopen("1126.out","w",stdout);
# endif
  scanf("%d",&m);
  i=1;
  while(scanf("%d",&x)==1 && x!=-1){
    if(h<m){
      p[i]=++h;
      a[h]=i;
      v[i]=x;
      siftup(p[i]);
    }
    else{
      if(x>v[i]){
        v[i]=x;
        siftup(p[i]);
      }
      else{
        v[i]=x;
        siftdown(p[i]);
      }
    }
    if(h==m) printf("%d\n",v[a[1]]);
    i++;
    if(i==m+1) i=1;
  }
  return 0;
}
