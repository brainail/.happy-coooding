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

