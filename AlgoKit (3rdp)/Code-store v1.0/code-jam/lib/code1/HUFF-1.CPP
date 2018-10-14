#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>


int index[256],n=0,tn,freq[100],tree[50][2];
char alpha[50],tcode[50],codes[257][50];

int Min(int i,int j)
{
	return (freq[i]<freq[j]);
}
#include"pheap.h"

void Rec(int i,int l)
{
   if(tree[i][0]==0)
		{
		  tcode[l]=0;strcpy(codes[i],tcode);
		  return;
		}
   tcode[l]='0';
   Rec(tree[i][0],l+1);
   tcode[l]='1';
   Rec(tree[i][1],l+1);

}

void printcode()
{
  int i;
  for(i=1;i<=n;i++)
	 printf("%c  =  %s\n",alpha[i],codes[i]);
}

void main()
{
  FILE*f;
  int n1,n2;
  char filename[10],ch;
  clrscr();
  //scanf("%s",filename);
  f=fopen("zip-1.txt","r");
  while(ch!=EOF)
	 {
	   ch=fgetc(f);
	   if(index[ch]==0)
			  {
				 index[ch]=++n;
				 freq[n]=1;
				 alpha[n]=ch;
			  }
	   else freq[index[ch]]++;
	 }
  tn=n;
  HeapInit(n);
  Heapify();
  while(hn>1)
	 {
		n1=ExtractMin();
		n2=ExtractMin() ;
		freq[++tn]=freq[n1]+freq[n2];
		HeapInsert(tn);
		tree[tn][0]=n2;
		tree[tn][1]=n1;
	 }
  Rec(tn,0);
  printcode();
  getch();
}