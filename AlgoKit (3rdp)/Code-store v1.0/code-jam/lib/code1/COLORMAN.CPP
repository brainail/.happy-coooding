#include<stdio.h>
#include<conio.h>
#include<limits.h>

int Cost[25][25][4][5];
int rear,front,sr,sc,dr,dc;
struct QUE{int r,c,d,cl,p;}Q[20*20*4];
int Gr[4]={-1,0,1,0};
int Gc[4]={0,-1,0,1};

void Init(int row,int col)
{
  int r,c,d,cl;
  for(r=0;r<=row+1;r++)
      for(d=0;d<=4;d++)
	 for(cl=0;cl<5;cl++)

	    Cost[r][0][d][cl]=Cost[r][col+1][d][cl]=0;

  for(c=0;c<=col+1;c++)
      for(d=0;d<=4;d++)
	 for(cl=0;cl<5;cl++)

	    Cost[0][c][d][cl]=Cost[row+1][c][d][cl]=0;
}

int Input(void)
{
  int r,c,d,cl,M,N,v;
  char ch;
  scanf("%d%d",&M,&N);
  if(M==0 && N==0) return 0;
  Init(M,N);
  for(r=1;r<=N;r++){
  scanf("\n");
  for(c=1;c<=N;c++)
  {
    scanf("%c",&ch);
    if(ch=='#') v=0;
    else
	{
	  if(ch=='S') {sr=r;sc=c;}
	  else if(ch=='T') {dr=r;dc=c;}
	  v=INT_MAX;
	}
    for(d=0;d<=4;d++)
       for(cl=0;cl<5;cl++)
       Cost[r][c][d][c]=v;
  }
}scanf("\n");
return 1;
}
void EnQ(int r,int c,int d,int cl)
{
   Q[rear].r=r;
   Q[rear].c=c;
   Q[rear].d=d;
   Q[rear].cl=cl;
   rear++;
}
int DeQ(int *r,int *c,int *d,int *cl)
{
  if(rear==front) return 0;
  *r=Q[front].r;
  *c=Q[front].c;
  *d=Q[front].d;
  *cl=Q[front].cl;
  front++;
  return 1;
}

Valid(int r,int c,int d,int cl,int nr,int nc,int nd,int ncl,int cst)
{
  if(Cost[nr][nc][nd][ncl] > Cost[r][c][d][cl]+cst)
  {
    Cost[nr][nc][nd][ncl]=Cost[r][c][d][cl]+cst;
    return 1;
  }
  return 0;
}
int BFS(void)
{
    int r,c,d,cl;
    Cost[sr][sc][0][0]=0;
    EnQ(sr,sc,0,0);
    while(DeQ(&r,&c,&d,&cl))
    {
      if(r==dr && c==dc && cl==0) return 1;
      if(Valid(r,c,d,cl,r+Gr[d],c+Gc[d],d,(cl+1)%5,1))
	EnQ(r+Gr[d],c+Gc[d],d,(cl+1)%5);
      if(Valid(r,c,d,cl,r,c,(d+1)%4,cl,1))
	EnQ(r,c,(d+1)%4,cl);
      if(Valid(r,c,d,cl,r,c,(d+3)%4,cl,1))
	EnQ(r,c,(d+3)%4,cl);
    }
    return 0;
}
void main()
{
   int Case=0,dd=0,d;
   freopen("mono.in","r",stdin);
   while(Input())
   {
     printf("Case #%d\n",++Case);
     if(BFS())
     {
	for(d=1;d<4;d++)
	    if(Cost[dr][dc][dd][0] > Cost[dr][dc][d][0])
	      dd=d;
	      printf("minimum time=%d sec\n",Cost[dr][dc][dd][0]);

     }else
     printf("Destination Not reachable");
   }
}
