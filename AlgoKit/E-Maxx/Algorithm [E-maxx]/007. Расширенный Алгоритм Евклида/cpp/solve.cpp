#include<iostream>
using namespace std;

long long euclid(long long a,long long b,long long &x,long long &y) {
 long long x0,y0,g;
 if(a==0) { x=0; y=1; return b; }
 g=euclid(b%a,a,x0,y0);
 x=y0-(b/a)*x0; y=x0;
 return g;
}

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 long long a,b,x,y;
 scanf("%lld %lld",&a,&b);
 long long gcd=euclid(a,b,x,y);
 printf("%lld * %lld + %lld * %lld = %lld",a,x,b,y,gcd);
}

