/* @JUDGE_ID: 6401 374 C */

# include <stdio.h>

int main(void)
{ 
  unsigned long r,b,p,m,t;
  while(scanf("%lu",&b)==1){
    scanf("%lu%lu",&p,&m);
    t=1;
    t<<=30;
    if(p==0){
      printf("1\n");
      continue;
    }
    while(!(t&p))
      t>>=1;
    r=1;
    while(t){
      r=(r*r)%m;
      if(t&p)
	r=(r*(b%m))%m;
      t>>=1;
    }
    printf("%lu\n",r);
  }
  return 0;
}
