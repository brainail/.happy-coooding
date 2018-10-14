# include <math.h>

int mod(int a,int b)
{
  int q=floor(1.0*a/b);
  return a-q*b;
}

int divide(int a,int b)
{
  int q=floor(1.0*a/b);
  return q;
}

int gcd(int a,int b,int &xv,int &yv)
{
  int x[3]={1,0},y[3]={0,1},r[3],q;
  int i=0,j=1,k=2;
  r[0]=a;
  r[1]=b;
  while(r[j]){
	q=divide(r[i],r[j]);
	x[k]=x[i]-q*x[j];
	y[k]=y[i]-q*y[j];
	r[k]=mod(r[i],r[j]);
	i=(i+1)%3;
	j=(j+1)%3;
	k=(k+1)%3;
  }
  xv=x[i];
  yv=y[i];
  return r[i];
}