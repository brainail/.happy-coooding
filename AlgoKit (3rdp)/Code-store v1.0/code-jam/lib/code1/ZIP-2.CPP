#include<stdio.h>
#include<conio.h>
#include<io.h>
#include<dos.h>
#include<math.h>

  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  int total,height,lad;
  struct{int num;char chr;}heap[100];
  struct{int num;char chr;}node[27],temp;

  sort()
  {
    int ii,jj;
    for(ii=1;ii<27;ii++)
    {
      for(jj=1;jj<27;jj++)
      {
      if(node[ii].num < node[jj].num)
      {
	temp=node[ii];
	node[ii]=node[jj];
	node[jj]=temp;
      }
      }
    }
  }
  hepcre(int lad,int tt)
  {
    int tmp=total+1;
    while(tt!=tmp)
    {
    heap[lad].num=node[tt].num;
    heap[lad].chr=node[tt].chr;
    tt++;
    lad--;
    }
  }

main()
      { char ch;
	FILE *fp;
	clrscr();
	fp=fopen("zip1.txt","r");
	if(fp==NULL) printf("\nThere is no file");
	else
	while(!feof(fp))
	{
	  ch=fgetc(fp);
	 switch(ch)
		  {
		   case 'a': a+=1; node[1].num=a;node[1].chr='a';break;
		   case 'b': b+=1; node[2].num=b;node[2].chr='b';break;
		   case 'c': c+=1; node[3].num=c;node[3].chr='c';break;
		   case 'd': d+=1; node[4].num=d;node[4].chr='d';break;
		   case 'e': e+=1; node[5].num=e;node[5].chr='e';break;
		   case 'f': f+=1; node[6].num=f;node[6].chr='f';break;
		   case 'g': g+=1; node[7].num=g;node[7].chr='g';break;
		   case 'h': h+=1; node[8].num=h;node[8].chr='h';break;
		   case 'i': i+=1; node[9].num=i;node[9].chr='i';break;
		   case 'j': j+=1; node[10].num=j;node[10].chr='j';break;
		   case 'k': k+=1; node[11].num=k;node[11].chr='k';break;
		   case 'l': l+=1; node[12].num=l;node[12].chr='l';break;
		   case 'm': m+=1; node[13].num=m;node[13].chr='m';break;
		   case 'n': n+=1; node[14].num=n;node[14].chr='n';break;
		   case 'o': o+=1; node[15].num=o;node[15].chr='o';break;
		   case 'p': p+=1; node[16].num=p;node[16].chr='p';break;
		   case 'q': q+=1; node[17].num=q;node[17].chr='q';break;
		   case 'r': r+=1; node[18].num=r;node[18].chr='r';break;
		   case 's': s+=1; node[19].num=s;node[19].chr='s';break;
		   case 't': t+=1; node[20].num=t;node[20].chr='t';break;
		   case 'u': u+=1; node[21].num=u;node[21].chr='u';break;
		   case 'v': v+=1; node[22].num=v;node[22].chr='v';break;
		   case 'w': w+=1; node[23].num=w;node[23].chr='w';break;
		   case 'x': x+=1; node[24].num=x;node[24].chr='x';break;
		   case 'y': y+=1; node[25].num=y;node[25].chr='y';break;
		   case 'z': z+=1; node[26].num=z;node[26].chr='z';break;
		  }

	}
	sort();
	if(a!=0)printf("a=%d\t",a);
	if(b!=0)printf("b=%d\t",b);
	if(c!=0)printf("c=%d\t",c);
	if(d!=0)printf("d=%d\t",d);
	if(e!=0)printf("e=%d\t",e);
	if(f!=0)printf("f=%d\t",f);
	if(g!=0)printf("g=%d\t",g);
	if(h!=0)printf("h=%d\t",h);
	if(i!=0)printf("i=%d\t",i);
	if(j!=0)printf("j=%d\t",j);
	if(k!=0)printf("k=%d\t",k);
	if(l!=0)printf("l=%d\t",l);
	if(m!=0)printf("m=%d\t",m);
	if(n!=0)printf("n=%d\t",n);
	if(o!=0)printf("o=%d\t",o);
	if(p!=0)printf("p=%d\t",p);
	if(q!=0)printf("q=%d\t",q);
	if(r!=0)printf("r=%d\t",r);
	if(s!=0)printf("s=%d\t",s);
	if(t!=0)printf("t=%d\t",t);
	if(u!=0)printf("u=%d\t",u);
	if(v!=0)printf("v=%d\t",v);
	if(w!=0)printf("w=%d\t",w);
	if(x!=0)printf("x=%d\t",x);
	if(y!=0)printf("y=%d\t",y);
	if(z!=0)printf("z=%d\t",z);
	total=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z;
	printf("\n%d",total);
	int tt=total+1;
	while(tt!=1)
	{
	 tt=tt/2;
	 height+=1;
	}
	printf(" %d",height);
	lad=(pow(2,height))-1;
	printf("\n%d",lad);
	tt=1;
	while(node[tt].num==0)
	{
	 tt++;
	}
	hepcre(lad,tt);
	getch();
}