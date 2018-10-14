/* Heap class : Index heap */

# include <stdio.h>

# define M 10001

class Heap{
  int h,a[M],p[M];
  int (*fcmp)(int,int);
  void swap(int i,int j);
  void siftup(int i);
  void siftdown(int i);
public:
  void clear(void);
  void setfcmp(int (*f)(int,int));
  int isempty(void);
  void insert(int newval);
  void remove(int oldval);
  int top(void);
  void extract(void);
};

void Heap::swap(int i,int j)
{
  int t=a[i];
  a[i]=a[j];
  a[j]=t;
  p[a[i]]=i;
  p[a[j]]=j;
}

void Heap::siftup(int i)
{
  while(i>1 && (*fcmp)(a[i],a[i/2])<0){
    swap(i,i/2);
    i/=2;
  }
}

void Heap::siftdown(int i)
{
  int optimal,left,right;
  while(1){
    optimal=i;
    left=2*i;
    right=left+1;
    if(left<=h && (*fcmp)(a[left],a[optimal])<0)
      optimal=left;
    if(right<=h && (*fcmp)(a[right],a[optimal])<0)
      optimal=right;
    if(i==optimal) break;
    swap(i,optimal);
    i=optimal;
  }
}

void Heap::clear(void)
{
  h=0;
}

void Heap::setfcmp(int (*f)(int,int))
{
  fcmp=f;
}

int Heap::isempty(void)
{
  return h==0;
}

void Heap::insert(int newval)
{
  a[++h]=newval;
  p[a[h]]=h;
  siftup(h);
}

void Heap::remove(int oldval)
{
  int i=p[oldval];
  a[i]=a[h--];
  p[a[i]]=i;
  siftdown(i);
  siftup(i);
}

int Heap::top(void)
{
  return a[1];
}

void Heap::extract(void)
{
  a[1]=a[h--];
  p[a[1]]=1;
  siftdown(1);
}

int cmp1(int u,int v)
{
  return u-v;
}

int cmp2(int u,int v)
{
  return v-u;
}

# define N 3*M

Heap minHeap,maxHeap;
int n,rlen,rlist[N+1],rc;
int c[M];

int main(void)
{
  int i,policy,val;
  char s[2];
  minHeap.setfcmp(cmp1);
  maxHeap.setfcmp(cmp2);
//  freopen("2514.in","r",stdin);
  scanf("%d",&n);
  while(1){
    for(i=1;i<=N;i++) rlist[i]=0;
    scanf("%d",&rlen);
    for(i=0;i<rlen;i++){
	scanf("%d",&val);
      rlist[val]=1;
    }
    for(i=1;i<=n;i++) c[i]=0;
    minHeap.clear();
    maxHeap.clear();
    policy=1;
    rc=0;
    while(scanf("%s",s)==1 && s[0]!='e'){
      if(s[0]=='a'){
        scanf("%d",&val);
        if(c[val]==0){
          minHeap.insert(val);
          maxHeap.insert(val);
        }
        c[val]++;
      }
      else if(s[0]=='r'){
        if(minHeap.isempty())
          val=-1;
        else if(policy==1){
          val=minHeap.top();
          c[val]--;
          if(c[val]==0){
            minHeap.extract();
            maxHeap.remove(val);
          }
        }
        else{
          val=maxHeap.top();
          c[val]--;
          if(c[val]==0){
            maxHeap.extract();
            minHeap.remove(val);
          }
        }
        rc++;
        if(rlist[rc]) printf("%d\n",val);
      }
      else if(s[0]=='p')
        scanf("%d",&policy);
    }
    if(scanf("%d",&n)==1) printf("\n");
    else break;
  }
  return 0;
}
