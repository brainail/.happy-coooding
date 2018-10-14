#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<dos.h>
#include<io.h>
#include<stdlib.h>

int tree[50][2],n,numvl,numofcar[257];
char car[257],alpha[50],tcode[50],codes[257][50];
int a;

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


main()
{
 int fl,o,i=1,j=0,tn,re,scr=1,k=1,l=0,m=0;
 char ex0,ch,are[9],cds[16];
 FILE *fp,*ft,*f;
 clrscr();
fp=fopen("pqr.txt","r");
f=fopen("zhid.txt","w");
printf("%c",128);
exit(0);
while(!eof(0))
{
  ch=fgetc(fp);
  fprintf(f,"%c",ch);
  printf("%d",ch);
}
exit(0);
fl=ftell(fp);
fseek(fp,-1,SEEK_END);
ex0=fgetc(fp);
printf("%c",ex0);
fseek(fp,fl,SEEK_SET);

 fscanf(fp,"%d",&n);
 printf("%d\n",n);
 tn=2*n-1;
 for(i=1;i<=n;i++)
 {
   ch=fgetc(fp);
   fscanf(fp,"%d",&a);
   tree[i+n][0]=a;
   ch=fgetc(fp);
   alpha[i]=ch;
   fscanf(fp,"%d",&a);
   tree[i+n][1]=a;
 }
 Rec(tn,0);
 printcode();

   while(ch!=' ')
 {
   ch=fgetc(fp);
   numvl=ch;
 }

 o=7;i=0;
 while(ch!=EOF)
 {
     o=7;
     ch=fgetc(fp);
     printf("%c",ch);
     if(ch==ex0) if(fgetc(fp)==EOF) break;
     else fseek(fp,-1L,SEEK_CUR);

     numvl=ch;
     if(numvl<0) numvl=256+numvl;
     while(numvl!=1)
	  {
	    re=numvl%2;
	    numvl/=2;
	    if(re==1) are[o--]='1';
	    else are[o--]='0';
	  }
	  are[o--]='1';
     while(o!=-1)
	    are[o--]='0';

     are[8]='\x0';
     j=0;
     while(are[j])
	  {
	    cds[i++]=are[j++];
	  }
     cds[i++]='\x0';
     i=0;l=0;

     while(cds[l]!='\x0')
	  {
	    k=1;
	    are[i++]=cds[l];
	    are[i]='\x0';
	    l++;
	    while(k!=n+1)
		{
		   scr=strcmp(are,codes[k]);
		   k++;
		   if(scr==0)
		     {  m=l;
			k--;
			printf("%c",alpha[k]);
			i=0;break;
		     }
		}
	  } i=0;
     while(cds[m]!='\x0')
	  {
	     cds[i++]=cds[m++];
	  }
	  cds[i]='\x0';
 }
 getch();
}