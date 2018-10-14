#include<stdio.h>
#include<conio.h>
#include<io.h>
#include<dos.h>

  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  int heap[51];

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
		   case 'a': a+=1; break;
		   case 'b': b+=1; break;
		   case 'c': c+=1; break;
		   case 'd': d+=1; break;
		   case 'e': e+=1; break;
		   case 'f': f+=1; break;
		   case 'g': g+=1; break;
		   case 'h': h+=1; break;
		   case 'i': i+=1; break;
		   case 'j': j+=1; break;
		   case 'k': k+=1; break;
		   case 'l': l+=1; break;
		   case 'm': m+=1; break;
		   case 'n': n+=1; break;
		   case 'o': o+=1; break;
		   case 'p': p+=1; break;
		   case 'q': q+=1; break;
		   case 'r': r+=1; break;
		   case 's': s+=1; break;
		   case 't': t+=1; break;
		   case 'u': u+=1; break;
		   case 'v': v+=1; break;
		   case 'w': w+=1; break;
		   case 'x': x+=1; break;
		   case 'y': y+=1; break;
		   case 'z': z+=1; break;
		  }

	}
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

	     printf("%d",17/2);

	getch();
}