#include<stdio.h>
#include<conio.h>
#define max 30
int dis[30],fin[30],n,u1,v1,dfn,adj[30][30];
int parent[30],status[30],top=0,stack[30][2];
int art[max];
int min(int x,int y){
	if(x<y)return x;
	return y;
}
void push(int u,int v){
	if(top==max)return;
	else{
		top++;
		stack[top][0]=u;
		stack[top][1]=v;
	}
}
void pop(){
	if(top==0)return;
	else{
		u1=stack[top][0];
		v1=stack[top][1];
		top--;
		}
}
void find_component(int u,int v){
	int c=0;
	while(1){
	c++;
	pop();
	printf("	%d-->%d",u1,v1);
	if(u1==u && v1==v)
		break;

			}
	if(c==1)
		printf("\nit is a bridge\n");
	else
		printf("\nit is a component\n");
}

void visit(int u){
	int v;
	dis[u]=fin[u]=++dfn;
	for(v=1;v<=n;v++){
		if(v!=parent[u] && adj[u][v]==1){
			if(dis[v]<dis[u])
				push(u,v);
		if(dis[v]==0){
			parent[v]=u;
			visit(v);
		if(dis[u]<=fin[v]){
			art[u]++;
			if(art[u]>0)
			printf("art:%d\n",u);
			find_component(u,v);
							}
		fin[u]=min(fin[u],fin[v]);
		}
	else{
		fin[u]=min(fin[u],dis[v]);
		}
	}
	}
}
void main(){
	int e,i,s,d;
	clrscr();
	FILE *fp;
	fp=fopen("art.txt","r");
	fscanf(fp,"%d%d",&n,&e);
	for(i=0;i<e;i++){
		fscanf(fp,"%d%d",&s,&d);
		adj[s][d]=1;
		adj[d][s]=1;
					}
	art[1]=-1;
	visit(1);
}