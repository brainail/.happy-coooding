#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//FILE *ft;

int index[256],n=0,tn,freq[100],tree[50][2],tcr;
char alpha[50],tcode[50],codes[257][50],enq[16];

int Min(int i,int j)
{
	return (freq[i]<freq[j]);
}
#include"pheap.h"

compress();
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
  f=fopen("pqr.txt","r");
  while(ch!=EOF)
	 {
	   ch=fgetc(f);
	   tcr+=1;
//	   printf("%c",ch);
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
  compress();
  getch();
}
compress()
{
   FILE *ft,*fp;
   char ch;
   int i=1,j=0,k=0,sum=0,l=0,tcr2=0;
  ft=fopen("zahid.zad","w");
  fp=fopen("pqr.txt","r");
  //fprintf(ft,"%d",tcr);
  //printf("%d",tcr);
  fprintf(ft,"%d,",n);
  printf("%d,",n);
  for(i=1;i<=n;i++)
  {
     fprintf(ft,"%d",tree[i+n][0]);
     fprintf(ft,"%c",alpha[i]);
     fprintf(ft,"%d,",tree[i+n][1]);
     printf("%d",tree[i+n][0]);
     printf("%c",alpha[i]);
     printf("%d,",tree[i+n][1]);
  }

  for(i=1;i<=n;i++)
  {
  //printf("%s",codes[i]);
  j=0;sum=0;
  //fprintf(ft,"%c",alpha[i]);
  //printf("%c",alpha[i]);
  //while(codes[i][j]!='\x0')  j++;
  j=strlen(codes[i]);
  k=j;
  l=j-1;
  j=0;
  while(j!=k)
  {
    if(codes[i][j]=='1')  sum=sum+pow(2,l);
    j++;l--;
  }
  //fprintf(ft,"%d",sum);
  //printf("%d",sum);
  }
  i=1;j=0;k=0;sum=0;l=0;
  fprintf(ft," ");
  while(ch!=EOF)
	 { i=1;k=0,sum=0;
	 tcr2++;
	   ch=fgetc(fp);
	   while(alpha[i]!=ch) i++;
	   while(codes[i][k])
	     {
	       enq[j]=codes[i][k];
	       enq[j+1]='\x0';
	       j++;k++;
	     }

	   if(tcr2==tcr)
	   {
	     if(j<7)
	     {
	      while(j!=8)
	       {enq[j]='0';
	       enq[j+1]='\x0';
	       j++;l++;}
	     }
	   }
	   if(j>7)
	   {
	    k=0;i=7;
	    while(k!=8)
	    {
	      if(enq[k]=='1') sum=sum+pow(2,i);
	      i--;k++;
	    }  i=0;
	    while(k!=j+1)
	    {
	      enq[i]=enq[k];
	      enq[i+1]='\x0';
	      i++;k++;
	    }
	    j=i-1;
	    printf("%c",sum);
	    fprintf(ft,"%c",sum);
	   }
	 }  printf("%d",l);
	    fprintf(ft,"%d",l);
fclose(ft);
}