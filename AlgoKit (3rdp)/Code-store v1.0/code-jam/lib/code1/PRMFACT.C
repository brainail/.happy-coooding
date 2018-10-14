/* "Prime factors" */
/* @JUDGE_ID: 6401 583 C */
# include <stdio.h>
# define SIZE 5000
void generate_prime(long d[])
{ int i,j;
  long num;
  d[0]=2;
  d[1]=3;
  d[2]=5;
  for(i=3,num=7;i<SIZE;i++,num++){
    while(1){
      for(j=0;d[j]<=num/2;j++)
	if((num%d[j])==0){
	  num++;
	  break;
	}
      if(d[j]>num/2)
	break;
    }
    d[i]=num;
  }
}
int main(void)
{ long prime[SIZE],g;
  int i;
  generate_prime(prime);
  while(scanf("%ld",&g)==1 && g){
    printf("%ld =",g);
    if(g<0){
      printf(" -1 x");
      g*=-1;
    }
    for(i=0;i<SIZE && g>1;i++)
      while((g%prime[i])==0){
	printf(" %ld",prime[i]);
	g/=prime[i];
	if(g>1)
	  printf(" x");
	else
	  printf("\n");
      }
    if(i==SIZE && g>1)
      printf(" %ld\n",g);
  }
  return 0;
}
