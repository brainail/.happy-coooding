	 //	a little problem
#include<stdio.h>
#include<string.h>
#include<limits.h>
#define INF INT_MAX

long Cost[20][20][4];
int Row, Col, rear, front, Sr, Sc, Sd, Dr, Dc;
struct QUE{ int r, c, d; } Q[1000];
int Path[20][20][4];
int R[4] = {-1, 0, 1, 0};
int C[4] = {0, -1, 0, 1};
int D[4] = {0, -1, 1};
char DD[4][20] = {"North", "West", "South", "East"};

void Read()
{
	int r, c, d;
	char i, dik[20];
	scanf("%d%d", &Row, &Col);
	for(r=0; r<=Row+1; r++)
	for(d=0; d<4; d++) Cost[r][0][d] = Cost[r][Col+1][d] = -1;
	for(c=0; c<=Col+1; c++)
	for(d=0; d<4; d++) Cost[0][c][d] = Cost[Row+1][c][d] = -1;
	for(r=1; r<=Row; r++)
	{
		scanf("\n");
		for(c=1; c<=Col; c++)
		{
			scanf("%c", &i);
			if(i=='#')
				for(d=0; d<4; d++) Cost[r][c][d] = -1;
			else
				for(d=0; d<4; d++) Cost[r][c][d] = INF;
			if(i=='S') Sr = r, Sc = c;
			else if(i=='D')	Dr = r, Dc = c;
		}
	}
	scanf("\n%s", dik);
	for(Sd=0; Sd<4; Sd++) if(strcmp(dik, DD[Sd])==0) break;
	Cost[Sr][Sc][Sd] = 0;
	rear = front = -1;
}

void EnQ(int r, int c, int d)
{
	rear++;
	Q[rear].r = r;
	Q[rear].c = c;
	Q[rear].d = d;
}

void DeQ(int *r, int *c, int *d)
{
	front++;
	*r = Q[front].r;
	*c = Q[front].c;
	*d = Q[front].d;
}

void BFS()
{
	int r, c, d, nr, nc, nd, i;
	EnQ(Sr, Sc, Sd);
	do
	{
		DeQ(&r, &c, &d);
		nr = r + R[d];
		nc = c + C[d];
		for(i=0; i<3; i++)
		{
			nd = (4+d+D[i]) % 4;
			if(Cost[nr][nc][nd] > Cost[r][c][d] + 1)
			{
				Cost[nr][nc][nd] = Cost[r][c][d] + 1;
				EnQ(nr, nc, nd);
				Path[nr][nc][nd] = i;
			}
			nr = r, nc = c;
		}
	} while(rear!=front);
}

void Output()
{
	int d, i, P[100], r, c, k, t;
	for(d=0, t=1; i<4; i++)
		if(Cost[Dr][Dc][i] < Cost[Dr][Dc][d]) d=i;
	printf("Minimum Cost: %d\n", Cost[Dr][Dc][d]);
	i = -1, r = Dr, c = Dc;
	do
	{
		P[++i] = Path[r][c][d];
		if(P[i] == 0)
		{
			k = (4+d-2) % 4;
			r = r + R[k];
			c = c + C[k];
		}
		else
		{
			d = (4+d-D[P[i]]) % 4;
		}
	} while(!(r==Sr && c==Sc && d==Sd));
	printf("<%d, %d>%10s\n", r, c, DD[d]);
	while(i>=0)
	{
		if(P[i]==0)
			r = r + R[d], c = c + C[d];
		else
			d = (4+d+D[P[i]]) % 4;
		printf("<%d, %d>%10s\n", r, c, DD[d]);
		i--;
	}
	printf("\n");
}

void main()
{
	Read();
	BFS();
	Output();
}