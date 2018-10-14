#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define N 260
#define NORM 1000
#define M 10000

FILE *fpR, *fpW;
int parent[N*2], charCount, mark[N], charSet[N], top = 0;
char res[N][100], stk[N], tmp[N], lt, str2[NORM], s[N];
int topB = -1, B[50], to = 0;
char c[M];

int popB()
{
	if(topB==-1)
		return -1;
	return B[topB--];
}

void pushB(int i)
{
	B[++topB] = i;
}

void initAll()
{
	for(int i=1; i<=charCount; i++)
		mark[charSet[i]] = i;
}

void print(char *str, int c)
{
	int d = getcolor();
	textcolor(c);
	cprintf("%s", str);
	textcolor(d);
}

void printStatus(char *str, int s)
{
	for(int i=1; i<=s; i++)
		printf(" ");
	print("[ ", 15);
	print(str, 10);
	print(" ]\r\n", 15);
}

void printProc(char *str)
{
	int d = getcolor();
	textcolor(7);
	cprintf("%s", str);
	textcolor(d);
}

void showCredits()
{
	print("\r\n\r\n[ ", 15); print("file deCompreesor", 12); print("]", 15);
	print("\r\n\r\nCopyright (C) ", 15); print("Uddin Muhammad Khabir",9); 
	print(". khabir17@hotmail.com\r\n", 15);
	print("American Internationl University - Bangladesh.\r\n", 15);
	print("Department: Computer Science. ID: 03-03795-1\r\n", 15);
	print("Course: Algorithms, Teacher: Mahboob Alam\r\n\r\n", 15);
}

void showError(int e)
{
	char str[NORM];
	textcolor(15);
	printf("\n");
	switch (e)
	{
		case 1:
			strcpy(str,"USAGES: comp.exe filenameToDeCompress");
			break;
		case 2:
			strcpy(str,"Fatal Error: Input file cannot be opened.");
			break;
		case 3:
			strcpy(str,"Fatal Error: Output file cannot be created.");
			break;
		case 4:
			strcpy(str,"Error: Array Limit Exceeded.");
			break;
	}
	print(str, 12);
	exit(1);
}

void checkUsages(int c)
{
	if(c!=2)
		showError(1);
}

void push(int i)
{
	stk[++top] = i;
}

int pop()
{
	if(top==0)
		return -1;
	return stk[top--];
}

void genCode()
{
	int i, k, cnt = 0;
	for(i=1; i<=charCount; i++, cnt = 0)
	{
		k=mark[charSet[i]];
		while(k!=parent[k])
		{
			k=parent[k];
			if(k<0)
				k = -k, res[i][cnt++] = '0';
			else
				res[i][cnt++] = '1';
		}
		strrev(res[i]);
	}
}

void openFile2Write(char str[])
{
	char str1[NORM];
	strcpy(str1,str);
	str1[strlen(str1)-3] = 0;
	strcat(str1,"txt");
	fpW = fopen(str1, "w+");
	if(fpW==NULL)
		showError(3);
}

void process(int n)
{
	while(n/2)
	{
		pushB(n % 2);
		n /= 2;
	}
	pushB(n%2);
	while((n=popB())!=-1)
	{
		if(to>=M)
			showError(4);
		c[to++] = n + '0';
	}
}

void readFromFile(char *fileName)
{
	fpR = fopen(fileName, "rb");
	if(fpR==NULL)
		showError(2);
	fscanf(fpR, "%d", &charCount);
	for(int i=1; i<=charCount; i++)
		fscanf(fpR, "%d", &charSet[i]);
	for(i=1; i<=2*charCount-1; i++)
		fscanf(fpR, "%d", &parent[i]);
	initAll();
}

void decode()
{
	int sa=0, i, len, j, flag, k;
//	lt = lt - '0';
	c[to] = 0;
	while(sa<to)
	{
		for(i=1; i<=charCount; i++)
		{
			len = strlen(res[i]), flag = 1, k = 0;
			for(j=sa; j<len; j++)
				if(res[i][k++]!=c[j])
				{
					flag = 0;
					break;
				}
			if(flag!=0)
			{
				sa += len;
				fprintf(fpW, "%c", charSet[i]);
			}
		}
	}
}

void readData()
{
	int ch, chT;
	long t;
	ch = fgetc(fpR);
	long ret = ftell(fpR);
	fseek(fpR, 0L, SEEK_END);
	t = ftell(fpR)-1;
	fseek(fpR, t, SEEK_SET);
	lt = fgetc(fpR);
	fseek(fpR, ret, SEEK_SET);
	while(ret!=t && (ch=fgetc(fpR))!=EOF)
	{
		process(ch);
		ret = ftell(fpR);
	}
	decode();
	fclose(fpR);
}

int main(int argc, char *argv[])
{
	clrscr();
	showCredits();
	checkUsages(argc);
	openFile2Write(argv[1]);
	readFromFile(argv[1]);
	genCode();
	readData();
	printStatus("DONE",8);
	return 0;
}