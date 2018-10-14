#include<stdio.h>
int a[20][20],x[20],n;
void next(int k)
{
	int j;
	while(1)
	{
		x[k]=(x[k]+1)%(n+1);
		if(x[k]==0)
			return;
		if((a[x[k-1]][x[k]])!=0)
		{
			for(j=1;j<=k-1;j++)
				if(x[k]==x[j])
					break;
			if(j==k)
				if((k<n)||(k==n&&a[x[n]][x[1]]!=0))
					return;
		}
	}
}
void hamilt(int k)	
{
	int j;
	while(1)
	{
		next(k);
		if(x[k]==0)
			return;
		if(k==n)
		{
			printf("    ");
			for(j=1;j<=n;j++)
				printf("%2d",x[j]);
		}
		else
			hamilt(k+1);
	}
}
void main()
{
	int i,u,v;
	x[1]=1;
	printf("\n\n  Enter how many nodes(0<n<20) :");
	scanf("%d",&n);
	printf("\n\n  Enter your edges(ex- u sp v)(press 'e' for end) : \n");
	for(i=1;i<=(n*n)/2;i++)
	{
		if(getchar()=='e')
			break;
		scanf("%d%d",&u,&v);
		a[u][v]=a[v][u]=1;
	}
	hamilt(2);
	printf("\n\n");
}