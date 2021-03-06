#include<iostream>
#include<stdio.h>
using namespace std;

const int SIZE = 2000010;
const int BASE = 51123987;

int n, l1 = -1, l2 = -1, r1 = -1, r2 = -1, x, d1[SIZE], d2[SIZE], p2[SIZE];
long long p1[SIZE], ans = 0;
char a[SIZE];

int main() {
 scanf("%d\n",&n);
 for(int i=0; i<n; i++) a[i]=getchar(), p1[i]=p2[i]=0;
 p1[n]=p2[n]=0;
 for(int i=0; i<n; i++) {
  x = (i>r1 ? 0 : min(d1[l1+r1-i],r1-i));
  while(i-x>0 && i+x+1<n && a[i-x-1] == a[i+x+1]) ++x;
  if(i+x>r1) r1=i+x, l1=i-x; 
  d1[i] = x;
  x = (i+1>r2 ? -1 : min(d2[l2+r2-i-1],r2-i-1));
  while(i-x>0 && i+x+2<n && a[i-x-1] == a[i+x+2]) ++x;
  if(i+x+1>r2) r2=i+x+1, l2=i-x; 
  d2[i] = x; 
  p1[i-d1[i]]++, p1[i+1]--, p2[i+d1[i]]++, p2[i-1]--;
  if(d2[i]>=0) p1[i-d2[i]]++, p1[i+1]--;
  if(d2[i]>=0) p2[i+d2[i]+1]++, p2[i]--; 
  ans += d1[i] + d2[i] + 2;
  if(ans > BASE) ans -= BASE;
 }
 for(int i=1; i<n; i++) p1[i]+=p1[i-1];
 p1[n]=p2[n]=0;
 for(int i=n-1; i>=0; i--) p1[i]+=p1[i+1], p2[i]+=p2[i+1];
 if(ans % 2 == 0) ans=((ans/2)*(ans-1)) % BASE; else ans=(ans*((ans-1)/2)) % BASE;
 for(int i=0; i<n; i++) ans=(ans-(p2[i]*p1[i+1])) % BASE;
 printf("%d\n",(ans+BASE)%BASE);
}

