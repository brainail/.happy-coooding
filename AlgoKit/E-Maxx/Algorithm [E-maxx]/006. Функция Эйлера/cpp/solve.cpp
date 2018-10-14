#include<iostream>
using namespace std;

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 long long n;
 scanf("%lld",&n);
 long long ans=n;
 for(long long i=2; i*i<=n; i++) 
  if(n%i==0) {
   while(n%i==0) n/=i;
   ans-=ans/i;
  }
 if(n>1) ans-=ans/n;
 printf("%lld",ans); 
}

