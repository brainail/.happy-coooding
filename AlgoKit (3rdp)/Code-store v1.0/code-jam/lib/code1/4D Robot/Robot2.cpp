#include<stdio.h>

#define MaxM 57l
#define MaxN 57l
#define INF MaxM*MaxN*5l

#define QSIZE MaxN*MaxM
//#define white 1
//#define gray 2
//#define black 3
char A[MaxM][MaxN];//Board
int M,N;

long cost[MaxM][MaxN][5];// 3d cost matrix for cost of each state, row,column, face
int front=0;
int rear=0;
struct info
{
 int r,c,f;//robot state
};
info start,end,Queue[QSIZE+2];



void Enqueue(info item)
{
 rear++;
 if(front==rear)
 {
  printf("Error:Queue is full!\n");
  if(front==0)
	rear=QSIZE-1;
  else
	rear=rear-1;
 }
 else
  Queue[rear]=item;
}

info Dequeue()
{
 info item;
 if(front==rear)
 {
  printf("Error:Queue is empty!\n");
 }

 else
 {
  front++;
  item=Queue[front];
 }
 return item;
}

int isempty()
{
	return (front-rear);
}

int fun(int u,int v,int x,info y)
{
	if(A[u][v]!='#')
	{
			if(cost[u][v][x] > cost[y.r][y.c][y.f]+1)
			{
				cost[u][v][x]=cost[y.r][y.c][y.f]+1;

				y.r=u;
				y.c=v;
				y.f=x;

				Enqueue(y);
			}
			return 1;
	}
	return 0;
}
void BFS()
{
 info u,v;
 int i,j,k;

 //Cost Matrix initialization

 for(i=0;i<=N+3;i++)
	for(j=0;j<=M+3;j++)
		for(k=0;k<5;k++)
			cost[i][j][k]= INF;

 
cost[start.r][start.c][start.f]=0;
Enqueue(start);

	while(isempty())
	{
		u=Dequeue();
		
		//New states generated 3 for moves, two for rotate
		//f = 1 means North, 2 means East, 3 means South, 4 means West
		
		if(u.f==1)
		{
			fun(u.r,u.c,2,u); 
			fun(u.r,u.c,4,u);
			if( fun(u.r-1,u.c,1,u) )
			if( fun(u.r-2,u.c,1,u) )
				fun(u.r-3,u.c,1,u);
		 }
		else if(u.f==2)
		{
			fun(u.r,u.c,3,u);
			fun(u.r,u.c,1,u);
			if( fun(u.r,u.c+1,2,u) )
			if( fun(u.r,u.c+2,2,u) )
				fun(u.r,u.c+3,2,u);
		 }
		else if(u.f==3)
		{
			fun(u.r,u.c,4,u);
			fun(u.r,u.c,2,u);
			if( fun(u.r+1,u.c,3,u) )
			if( fun(u.r+2,u.c,3,u) )
				fun(u.r+3,u.c,3,u);
		 }
		else
		{
			fun(u.r,u.c,1,u);
			fun(u.r,u.c,3,u);
			if( fun(u.r,u.c-1,4,u) )
			if( fun(u.r,u.c-2,4,u) )
				fun(u.r,u.c-3,4,u);
		 }
	}
}

void main()
{
 int i,j,t;
 char s[100];
 long min;
 freopen("cost.in","r",stdin);

 while(scanf("%d%d",&M,&N)==2 && (M || N))
 {
	M=M+3;
	N=N+3;

	for(i=3;i<M;i++)
		for(j=3;j<N;j++)
			A[i][j]='.';

	for(i=0;i<=M+3;i++)
		A[i][0]=A[i][1]=A[i][2]=A[i][3]=A[i][N]=A[i][N+1]=A[i][N+2]='#';

	for(i=0;i<=N+3;i++)
		A[0][i]=A[1][i]=A[2][i]=A[3][i]=A[M][i]=A[M+1][i]=A[M+2][i]='#';

	for(i=3;i<M;i++)
		for(j=3;j<N;j++)
		{
			scanf("%d",&t);
			if(t==1)
				A[i][j]=A[i+1][j]=A[i][j+1]=A[i+1][j+1]='#';
		}

		scanf("%d%d%d%d",&start.r,&start.c,&end.r,&end.c);
		scanf("%s",s);
		start.r += 3;
		start.c += 3;
		end.r += 3;
		end.c += 3;

		switch(s[0])
		{
			case 'n':	start.f=1; break;
			case 'e':	start.f=2; break;
			case 's':	start.f=3; break;
			case 'w':	start.f=4; break;
		}

	   BFS();
	   min=INF;
	   for(i=1;i<=4;i++)
			if(cost[end.r][end.c][i]<min)
				min=cost[end.r][end.c][i];

	   if(min==INF)
	   puts("-1");
	   else
	   printf("%d\n",min);
	}

}

