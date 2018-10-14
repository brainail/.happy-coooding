#include<stdio.h>
int q[11],f=1,r=1,n;
void enque(int x)
{
	if(r==n+1)
		return;
	else
	{
		q[r]=x;
		r++;
	}
}
int deque()
{
	int x;
	if(f==n+1&&r==n+1)
		return 0;
	else
	{
		x=q[f];
		f++;
		return x;
	}
}
void main()
{
	int i,j,a[11][11],b[11][11],c[11],d[11],p[11],u,v,k,x;
	for(i=1;i<11;i++)
		for(j=1;j<11;j++)
			a[i][j]=0;
	printf("\n\n  Enter how many nodes(0<n<11) :");
	scanf("%d",&n);
	printf("\n\n  Enter your edges(ex- u sp v)(press 'e' for end) : \n");
	for(i=1;i<=(n*n)/2;i++)
	{
		if(getchar()=='e')
			break;
		scanf("%d%d",&u,&v);
		a[u][v]=a[v][u]=1;
	}
	for(i=1;i<=n;i++)
	{
		k=1;
		for(j=1;j<=n;j++)
			if(a[i][j])
			{
				b[i][k]=j;
				k++;
			}
		b[i][k]=0;
	}
	printf("\n\n  Which vertex is the root : ");
	scanf("%d",&x);
	for(i=1;i<=n;i++)
	{
		c[i]=1;
		d[i]=25000;
		p[i]=0;
	}
	c[x]=2;
	d[x]=0;
	p[x]=0;
	enque(x);
	while(f!=n+1&&r!=n+1)
	{
		u=deque();
		for(i=1;b[u][i]!=0;i++)
		{
			v=b[u][i];
			if(c[v]==1)
			{
				c[v]=2;
				d[v]=d[u]+1;
				p[v]=u;
				enque(v);
			}
		}
		c[u]=3;
	}
	printf("\n\n  The vulues of vertice in BFS : \n\n");
	printf("\n  nodes  values\n\n");
	for(i=1;i<=n;i++)
		printf("\n%5d%5d",i,d[i]);
	printf("\n\n");
}





























