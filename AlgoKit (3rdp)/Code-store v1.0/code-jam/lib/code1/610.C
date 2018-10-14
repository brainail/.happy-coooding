/* "Street directions" : Bridge finding */

/* @begin_of_source_code */
/* @JUDGE_ID: 6401 610 C */

# include <stdio.h>

# define _MIN(A,B) (((A)<(B))? (A):(B))
# define SIZE 1000

int n,v[SIZE],d[SIZE][SIZE],l[SIZE];
int c;

void check(int i,int p)
{ 
  int j;
  v[i]=c++;
  l[i]=v[i];
  for(j=0;j<n;j++)
    if(d[i][j] && j!=p){
      if(v[j]==-1){
	  check(j,i);
	  l[i]=_MIN(l[i],l[j]);
      }
      else
	  l[i]=_MIN(l[i],v[j]);
      if(l[j]<=v[i])
	  d[j][i]=0;
    }
}

int main(void)
{ 
  int T,m,case_no;
  int i,j;
  scanf("%d",&T);
  while(T--){
    case_no=1;
    while(scanf("%d%d",&n,&m)==2){
      if(n==0 && m==0) break;
      for(i=0;i<n;i++){
	v[i]=-1;
	for(j=0;j<n;j++)
	  d[i][j]=0;
      }
      while(m--){
	scanf("%d%d",&i,&j);
	d[i-1][j-1]=d[j-1][i-1]=1;
      }
      c=0;
      check(0,-1);
      printf("%d\n\n",case_no++);
      for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	  if(d[i][j])
	    printf("%d %d\n",i+1,j+1);
      printf("#\n");
    }
    if(T)
      printf("\n");
  }
  return 0;
}

/* @end_of_source_code */
