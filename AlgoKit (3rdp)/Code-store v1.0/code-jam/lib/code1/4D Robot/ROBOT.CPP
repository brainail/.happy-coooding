#include<stdio.h>
#include<string.h>
#include<limits.h>
#define max 20
struct que{int r,c,d,parent;}q[1000];

int m[max][max],sd,cost[max][max][4],D[4]={0,-1,1},rear,front;
int sr,sc,dr,dc,row,col,path[max][max][4],index[3];
char DD[4][10]={"north","west","south","east"};
int R[4]={-1,0,1,0},C[4]={0,-1,0,1};
void convert(int r,int c){
	int i,j,d;
	for(i=0;i<=r;i++){
	for(j=0;j<=c+1;j++){
	for(d=0;d<4;d++){
		if(j==1 || j==c+1)cost[i][j][d]=-1;
		else if(i==0 || i==r)cost[i][j][d]=-1;
		else cost[i][j][d]=INT_MAX;
	}
	}
	}
	for(i=1;i<=r;i++){
	for(j=1;j<=c+1;j++){
		if(m[i][j]==1){
			for(d=0;d<4;d++)
				cost[i][j][d]=cost[i][j+1][d]=cost[i-1][j][d]=cost[i-1][j+1][d]=-1;
					   }
						}
	}                 }

void enq(int r,int c,int d,int parent){
	rear++;
	q[rear].r=r;
	q[rear].c=c;
	q[rear].d=d;
	q[rear].parent=parent;
}
void deq(int *r,int *c,int *d){
	front++;
	*r=q[front].r;
	*c=q[front].c;
	*d=q[front].d;
}
void bfs(){
	int r,c,d,nr,nc,nd,i,k,l_cost,lr,lc,in=0;
	enq(sr,sc,sd,-1);

	  while(1){

		if(rear==front)break;
		deq(&r,&c,&d);
		l_cost=cost[r][c][d];
		for(k=0;k<3;k++){
			if(k>0)l_cost=cost[r][c][d]+1;
			nd=(4+d+D[k])%4;

			lr=r;lc=c;
			for(i=0;i<3;i++){
				nr=lr+R[nd];
				nc=lc+C[nd];

				if(cost[nr][nc][nd]!=-1){
					lr=nr;lc=nc;

					if(cost[lr][lc][nd]>l_cost+1){
						enq(lr,lc,nd,front);
						cost[lr][lc][nd]=l_cost+1;
						if(lr==dr && lc==dc){
							index[in]=rear;in++;}
									}
					continue;
										}
				else break;
							}

		}
	  }

}


void main(){
	int temp,r,c,i,j,d;
	char t[10];
	FILE *fp;
	fp=fopen("alg3.txt","r");
	while(1){
	fscanf(fp,"%d%d",&row,&col);
	if(row==0 && col==0)break;
	for(i=1;i<=row;i++)
	for(j=1;j<=col;j++)
		fscanf(fp,"%d",&m[i][j]);
	fscanf(fp,"%d%d%d%d",&sr,&sc,&dr,&dc);
	sc+=1;
	dc+=1;
	fscanf(fp,"%s",&t);
	for(sd=0;sd<4;sd++){
	if(strcmp(t,DD[sd])==0)break;

					}
	rear=front=-1;
	convert(row,col);
	cost[sr][sc][sd]=0;
	bfs();

	for(d=0,i=1;i<4;i++)
		if(cost[dr][dc][i]<cost[dr][dc][d])d=i;
		printf("minimum cost :%d\n",cost[dr][dc][d]);

		}
   }
