/* Sieve */

/* @begin_of_source_code */
/* @judge_id: 6401 H C++ */

# include <stdio.h>
# include <math.h>

# define SIZE 2000000
# define LIMIT 30000000

void generate_prime(int p[])
{ 
  int b[1+LIMIT/32];
  int i,j,k;
  for(i=0;i<=LIMIT/32;i++)
    b[i]=0xffffffff;
  for(k=0,i=2;i<=LIMIT;i++)
    if(b[i/32]&(1<<(i%32))){
      p[k++]=i;
      for(j=2*i;j<=LIMIT;j+=i)
        b[j/32]&=~(1<<(j%32));
    }
}

int main(void)
{
  long long n,root,c;
  int p[SIZE];
  int i,j;
  generate_prime(p);
  while(scanf("%lld",&n)==1){
    root=sqrt(n);
    while(n>1 && n%2==0) n/=2;
    c=1;
    for(i=1;p[i]<=root;i++){
      j=0;
      while(n%p[i]==0){
        n/=p[i];
        j++;
      }
      c*=(j+1);
    }
    if(n>1) c*=2;
    printf("%lld\n",c);
  }
  return 0;
}
/* @end_of_source_code */
 