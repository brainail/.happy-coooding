/* "It's not a bug its a feature" : Dijkstra */
/* @judge_id: 6401 658 C++ */

# include <stdio.h>
# include <values.h>

# define M 100
# define N 20
# define SIZE 1048577

int m,n,h;
unsigned unit=1;
int d[SIZE];
int a[SIZE],ptr[SIZE];
char pr[N+1],rm[N+1];
int pru[M],prs[M];
int rmu[M],rms[M];
int time[M];

void Heapify(int i)
{
  int l,r,s,t,j;
  l=2*i;
  r=2*i+1;
  if(l<=h && d[a[l]]<d[a[i]]) s=l;
  else s=i;
  if(r<=h && d[a[r]]<d[a[s]]) s=r;
  if(s!=i){
    ptr[a[i]]=s;
    ptr[a[s]]=i;
    t=a[i];
    a[i]=a[s];
    a[s]=t;
    Heapify(s);
  }
}

void Adjust(int i)
{
  int key;
  key=a[i];
  while(i>1 && d[a[i/2]]>d[key]){
    ptr[a[i/2]]=i;
    a[i]=a[i/2];
    i/=2;
  }
  a[i]=key;
  ptr[key]=i;
}

int ExtractMin(void)
{
  int min;
  if(h<1 || d[a[1]]==MAXINT) return -1;
  min=a[1];
  a[1]=a[h];
  ptr[a[h]]=1;
  h--;
  Heapify(1);
  return min;
}

int isone(int x,int j)
{
  return x&(unit<<j);
}

void setone(int *x,int j)
{
  *x|=(unit<<j);
}

int main(void)
{
  int case_no=1;
  int i,j,u,v;
  while(scanf("%d%d",&n,&m)==2){
    if(n==0 && m==0) break;
    for(i=0;i<m;i++){
      scanf("%d%s%s",&time[i],pr,rm);
      pru[i]=0;
      prs[i]=0;
      rmu[i]=0;
      rms[i]=0;
      for(j=0;j<n;j++){
        if(pr[j]!='0')
          setone(&pru[i],j);
        if(pr[j]=='+')
          setone(&prs[i],j);
        if(rm[j]=='0')
          setone(&rmu[i],j);
        if(rm[j]=='+')
          setone(&rms[i],j);
      }
    }
    for(i=0,h=1;i<n;i++)
      h*=2;
    for(i=0;i<h;i++){
      d[i]=MAXINT;
      a[i+1]=i;
      ptr[i]=i+1;
    }
    d[h-1]=0;
    Adjust(ptr[h-1]);
    while(1){
      u=ExtractMin();
      if(u==-1 || u==0) break;
      for(i=0;i<m;i++)
	if(((u&pru[i])^prs[i])==0){
	  v=(u&rmu[i])|rms[i];
	  if(d[v]>d[u]+time[i]){
	    d[v]=d[u]+time[i];
	    Adjust(ptr[v]);
	  }
	}
    }
    printf("Product %d\n",case_no++);
    if(d[0]==MAXINT)
      printf("Bugs cannot be fixed.\n");
    else
      printf("Fastest sequence takes %d seconds.\n",d[0]);
    printf("\n");
  }
  return 0;
}
