#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>

#define NORM 10000
#define N 260


int mark[N], charSet[N], freq[N*2], parent[N*2];
int charCount, heap[N*2], hn, top=0, dc = -1;
char stk[N], s[11];
FILE *fp;

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
	print("\r\n\r\n[ ", 15); print("fileCompreesor", 12); print("]", 15);
	print("\r\n\r\nCopyright (C) ", 15); print("Uddin Muhammad Khabir",9);
	print("Email: khabir17@hotmail.com\r\n", 15);
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
			strcpy(str,"USAGES: comp.exe filenameToCompress");
			break;
		case 2:
			strcpy(str,"Fatal Error: Input file cannot be opened.");
			break;
		case 3:
			strcpy(str,"Fatal Error: Output file cannot be created.");
			break;
	}
	print(str, 12);
	exit(1);
}

void initAll()
{
	printProc("Initializing all... ");
	for(int i=1; i<=N; i++)
		mark[i] = 0;
	top = 0;
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

int minFreq(int i, int j)
{
	if(freq[i] < freq[j])
		return 1;
	return 0;
}

void initHeap(int n)
{
	hn = n;
	for(int i=0; i<=n; i++)
		heap[i] = i;
}

void adjust(int i)
{
	int p, c, e = heap[i]; p = i, c = i*2;
	while(c<=hn)
	{
		if(c<hn && minFreq(heap[c+1], heap[c]))
			c++;
		if(minFreq(heap[c], e))
			heap[p] = heap[c], p = c, c = p * 2;
		else
			break;
	}
	heap[p] = e;
}

int extractRoot()
{
	int e = heap[1];
	heap[1] = heap[hn--], adjust(1);
	return e;
}

void insert(int e)
{
	int p, c;
	heap[++hn] = e, c = hn,	p = hn/2;
	while(c>0)
		if(minFreq(e, heap[p]))
			heap[c] = heap[p], c = p, p = c / 2;
		else
			break;
	heap[c] = e;
}

void readFromFile(char *fileName)
{
	char c; charCount = 0;
	printProc("Reading from file... ");
	printStatus("DONE",8);
	FILE *fp = fopen(fileName, "rb");
	if(fp==NULL)
		showError(2);
	while((c=fgetc(fp))!=EOF)
		if(mark[c]== 0)
			mark[c] = ++charCount, freq[charCount] = 1, charSet[charCount] = c;
		else
			freq[mark[c]]++;
	initHeap(charCount);
	fclose(fp);
}

void closeFile2Write()
{
	fclose(fp);
}

void toDec()
{
	for(int i=0, v=0; i<8; i++)
		v = v<<1, v = v | (s[i]-'0');
	fputc((char)v, fp);
//	printf("%d\n",v);
}

void writeOnFile(int ch)
{
	int v, i; s[8] = 0; s[++dc] = ch + '0';
	if(dc==7)
		toDec(), dc = -1;
}

void writeHeader()
{
	fprintf(fp, "%d", charCount);
	for(int i=1; i<=charCount; i++)
		fprintf(fp, " %d", charSet[i]);
	for(i=1; i<=(2*charCount)-1; i++)
		fprintf(fp, " %d", parent[i]);
	fprintf(fp," ");
}

void genCode()
{
	printProc("Generating code... ");
	printStatus("DONE",10);
	printProc("Writing on file... ");
	printStatus("DONE",10);
	writeHeader();
	int i, k;
	for(i=1; i<=charCount; i++)
	{
		k=mark[charSet[i]];
		while(k!=parent[k])
		{
			k=parent[k];
			if(k<0)
				k = -k, push(0);
			else
				push(1);
		}
		while((k=pop())> -1)
			writeOnFile(k);
	}
	if(dc<7)
	{
		for(i=dc+1; i<8; i++)
			s[i] = '0';
		toDec();
		fputc(7-dc+'0', fp);
	}
	else
	{
		fputc(0+'0', fp);
	}
	closeFile2Write();
}

void genTree()
{
	printProc("Generating huffman tree... ");
	printStatus("DONE",2);
	int min1, min2, nd = charCount;
	while(hn>1)
	{
		min1 = extractRoot(), min2 = extractRoot();
		freq[++nd] = freq[min1] + freq[min2];
		insert(nd), parent[min1] = -nd, parent[min2] = nd;
	}
	parent[nd] = nd;
}

void checkUsages(int c)
{
	if(c!=2)
		showError(1);
}

void openFile2Write(char str[])
{
	char str1[NORM];
	strcpy(str1,str);
	str1[strlen(str1)-3] = 0;
	strcat(str1,"zip");
	fp = fopen(str1, "wb");
	if(fp==NULL)
		showError(3);
	printProc("Opening file to write... ");
	printStatus("DONE",4);
}

int main(int argc, char *argv[])
{
	clrscr();
	showCredits();
	checkUsages(argc);
	readFromFile(argv[1]);
	genTree();
	openFile2Write(argv[1]);
	genCode();
	closeFile2Write();
	printProc("Closing destination file... ");
	printStatus("DONE",1);
	printf("\n");
	return 0;
}