/* "Problem with the problem setter" : Network Flow */
/* @begin_of_source_code */
/* @judge_id: 6401 10092 C++ */
# include <stdio.h>
# include <alloc.h>
# define MAX_VERTICES 1024

class Edge{
  public:
    int u,v;
    int c,f;
    int cf;
    Edge *next;
};
class Graph{
  public:
    int vertex_count;
    int isvisited[MAX_VERTICES];
    Edge *v[MAX_VERTICES];
};

int m,n;
Graph g;
int f;

void dfs(int i)
{
  Edge *p,*q;
  if(i==m+n+1){
    f=1;
    return;
  }
  p=g.v[i];
  g.isvisited[i]=1;
  while(p){
    if(p->cf>0 && !g.isvisited[p->v])
      dfs(p->v);
    if(f==1){
      if(p->c>0){
	p->f++;
	p->cf--;
	q=g.v[p->v];
	while(q->v!=i)
	  q=q->next;
	q->cf++;
      }
      else{
	p->cf--;
	q=g.v[p->v];
	while(q && q->v!=i)
	  q=q->next;
	q->f--;
	q->cf++;
      }
      return;
    }
    p=p->next;
  }
}

int main(void)
{
  Edge *p,*q;
  int i,j,k;
  int t[21];
  while(scanf("%d%d",&m,&n)==2){
    if(m==0 && n==0) break;
    g.vertex_count=m+n+2;
    for(i=0;i<m+n+2;i++)
      g.v[i]=NULL;
    for(i=1;i<=m;i++){
      scanf("%d",&k);
      t[i]=k;
      p=new Edge;
      p->u=0;
      p->v=i;
      p->c=p->cf=k;
      p->f=0;
      p->next=g.v[0];
      g.v[0]=p;
      p=new Edge;
      p->u=i;
      p->v=0;
      p->c=p->f=p->cf=0;
      p->next=g.v[i];
      g.v[i]=p;
    }
    for(i=m+1;i<=m+n;i++){
      p=new Edge;
      p->u=i;
      p->v=m+n+1;
      p->c=p->cf=1;
      p->f=0;
      p->next=g.v[i];
      g.v[i]=p;
      p=new Edge;
      p->u=m+n+1;
      p->v=i;
      p->c=p->f=p->cf=0;
      p->next=g.v[m+n+1];
      g.v[m+n+1]=p;
      scanf("%d",&j);
      while(j--){
	scanf("%d",&k);
	p=new Edge;
	p->u=k;
	p->v=i;
	p->c=p->cf=1;
	p->f=0;
	p->next=g.v[k];
	g.v[k]=p;
	p=new Edge;
	p->u=i;
	p->v=k;
	p->c=p->cf=p->f=0;
	p->next=g.v[i];
	g.v[i]=p;
      }
    }
    f=1;
    while(f){
      for(i=0;i<m+n+2;i++)
	g.isvisited[i]=0;
      f=0;
      dfs(0);
    }
    f=1;
    p=g.v[0];
    while(p){
      if(p->f!=p->c){
	f=0;
	break;
      }
      p=p->next;
    }
    if(f==0)
      printf("0\n");
    else{
      printf("1\n");
      for(i=1;i<=m;i++){
	p=g.v[i];
	while(p){
	  if(p->f>0){
	    printf("%d%s",p->v-m,t[i]==1? "\n":" ");
	    --t[i];
	  }
	  p=p->next;
	}
      }
    }
    for(i=0;i<m+n+2;i++){
      p=g.v[i];
      while(p){
	q=p->next;
	delete p;
	p=q;
      }
    }
  }
  return 0;
}
/* @end_of_source_code */
