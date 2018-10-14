#include<stdio.h>
#include<conio.h>
#include<values.h>

#define N 105
#define MAX MAXINT

int act[N][N], Q[N*20][3], cost[N][N];
int a, p, b, m, n, fin, na, nb, front, rear;

void init()
{
	front = -1, rear = -1;
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			cost[i][j] = MAX;
	cost[0][0] = 0;
}

void nQ(int r, int c, int p)
{
	Q[++rear][0] = r, Q[rear][1] = c, Q[rear][2] = p;
}

void dQ(int *r, int *c, int *p)
{
	*r = Q[++front][0], *c = Q[front][1], *p = front;
}

void op(int i)
{
	int currCapA, currCapB;
	if(i==0)
		na = 0, nb = b;
	else if(i==1)
		nb = 0, na = a;
	else if(i==2)
		na = m, nb = b;
	else if(i==3)
		nb = n, na = a;
	else if(i==4)
	{
		if(!a && !b)
			return;
		currCapB = n - b;
		if(currCapB <= 0)
			return;
		if(a >= currCapB)
			nb = n, na = a, na -= currCapB;
		else
			nb = b, nb += a, na = 0;
	}
	else
	{
		if(!a && !b)
			return;
		currCapA = m - a;
		if(currCapA <= 0)
			return;
		if(b >= currCapA)
			na = m, nb = b, nb -= currCapA;
		else
			nb = 0, na = a, na += b;
	}
}

void bfs()
{
	nQ(0, 0, -1);
	do{

		dQ(&a, &b, &p);
		if(a==fin)
			break;
		for(int i=0; i<6; i++)
		{
			op(i); /* na, nb will b changed for this func
				  according to values of a, b
				*/
			if(cost[na][nb]>cost[a][b]+1)
			{
				cost[na][nb]=cost[a][b]+1;
				act[na][nb] = i;
				nQ(na, nb, p);
			}
		}
	} while (rear!=front);
}

void dfs(int p)
{
	int i = act[na][nb];
	if(p==-1)
		return;
	na = Q[p][0], nb = Q[p][1];
	dfs(Q[p][2]);
	if(i==0)
		printf("Empty A\n");
	else if(i==1)
		printf("Empty B\n");
	else if(i==2)
		printf("Fill A\n");
	else if(i==3)
		printf("Fill B\n");
	else if(i==4)
		printf("Pour A to B\n");
	else
		printf("Pout B to A\n");
}

void main()
{
	clrscr();
	while(scanf("%d%d%d", &m, &n, &fin)!=EOF)
	{
		printf("\n");
		init();
		bfs();
		dfs(Q[p][2]);
		printf("\n");
	}
}
