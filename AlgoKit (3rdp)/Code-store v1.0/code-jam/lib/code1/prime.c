# include <stdio.h>
# include <math.h>

# define SIZE 200

typedef unsigned long Big;

void generate_prime(Big d[])
{ 
  int i,j;
  Big num,root;
  d[0]=2;
  d[1]=3;
  d[2]=5;
  for(i=3,num=7;i<SIZE;i++){
    while(1){
      root=sqrt(num);
      for(j=0;d[j]<=root;j++)
	if((num%d[j])==0)
	  break;
      if(d[j]>root) break;
      num+=2;
    }
    d[i]=num;
    num+=2;
  }
}

int isprime(Big num,Big p[])
{
  Big root=sqrt(num);
  int i;
  for(i=0;p[i]<=root;i++)
    if(num%p[i]==0)
      return 0;
  return 1;
}

int main(void)
{
  unsigned long n,p[SIZE];
  generate_prime(p);
  printf("%lu\n",p[SIZE-1]);
/*  for(n=214748363;n>=1;n--)
    if(isprime(n,p))
      break;
  printf("%lu\n",n);*/
  return 0;
}
