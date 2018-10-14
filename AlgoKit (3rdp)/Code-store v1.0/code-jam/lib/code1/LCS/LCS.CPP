#include<stdio.h>
#include<string.h>

#define N 102

int mat[N][N], m, n;
char s[N][N], s1[N], s2[N];

void init()
{
	m = strlen(s1);
	n = strlen(s2);
	for(int i=0; i<N; i++)
		mat[i][0] = mat[0][i] = 0;
}

void LCS()
{
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			if(s1[i-1]==s2[j-1])
				mat[i][j] = mat[i-1][j-1] + 1, s[i][j] = 'c';
			else if(mat[i-1][j]>mat[i][j-1])
				mat[i][j] = mat[i-1][j], s[i][j] = 'u';
			else
				mat[i][j] = mat[i][j-1], s[i][j] = 'l';
}

void dfs(int i, int j)
{
	if(i==0 || j==0)
		return;
	if(s[i][j] == 'c')
	{
		dfs(i-1, j-1);
		printf("%c", s1[i-1]);
	}
	else if(s[i][j] == 'u')
		dfs(i-1, j);
	else
		dfs(i, j-1);
}

void main()
{
	freopen("in.txt", "r", stdin);
	while(gets(s1))
	{
		gets(s2);
		init();
		LCS();
		dfs(m, n);
		putchar('\n');
	}
}