#include<stdio.h>
#include<math.h>
int x[11],c=0;
int place(int k,int i)
{
	int j;
	for(j=1;j<k;j++)
		if((x[j]==i)||(abs(x[j]-i)==abs(j-k)))
			return 0;
	return 1;
}
void nqueen(int k,int n)
{
	int i,j;
	for(i=1;i<=n;i++)
		if(place(k,i))
		{
			x[k]=i;
			if(k==n)
			{
				c++;
				if(c%3==0)
					printf("\n\n");
				printf("  ");
				for(j=1;j<=n;j++)
					printf("%2d",x[j]);
			}
			else
				nqueen(k+1,n);
		}
}
void main()
{
	int n;
	printf("\n\n  Enter how many queens : ");
	scanf("%d",&n);
	nqueen(1,n);
	printf("\n\n  Total number of ways : %d",c);
	printf("\n\n");
}