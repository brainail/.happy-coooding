#include<cassert>
#include<iostream>
#include<stdio.h>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

const int SIZE = 160;
const int BASE = 51123987;

int m,n,a[SIZE],nx[SIZE][4],u=0,ans=0,g,dp[2][SIZE/3][SIZE/3][SIZE],w;
char ch;

int myabs(int x) {
 return (x < 0 ? -x : x);
}

int main() {
 scanf("%d\n",&n);
 assert(n >= 1 && n <= 150); 
 forr(i,1,n) {
  scanf("%c",&ch);
  assert(ch >= 'a' && ch <= 'c');
  a[i] = ch - 'a' + 1;
 }
 // rar
 m = 1;
 forr(i,2,n)
  if(a[i] != a[m]) a[++m] = a[i];
 forr(i,m+1,n) a[i] = 0;
 
 // find the nearest symbol
 forr(i,1,m) {
  nx[i][0] = nx[i][1] = nx[i][2] = nx[i][3] = 0;
  forr(j,i,m)
   if(!nx[i][a[j]]) nx[i][a[j]] = j;
 }
 
 // dp
 dp[0][0][0][1] = 1, g = (n+2) / 3; 
 forr(ka,0,g) {
  forr(bk,0,g) forr(ck,0,g) forr(pp,0,m) dp[u^1][bk][ck][pp] = 0;
  forr(kb,0,g) forr(kc,0,g) if(ka + kb + kc <= n) 
   forr(p,1,m) if(w = dp[u][kb][kc][p]) {
    if(nx[p][1]) dp[u^1][kb][kc][nx[p][1]]+=w-(dp[u^1][kb][kc][nx[p][1]]+w>BASE)*BASE;
    if(nx[p][2]) dp[u][kb+1][kc][nx[p][2]]+=w-(dp[u][kb+1][kc][nx[p][2]]+w>BASE)*BASE;
    if(nx[p][3]) dp[u][kb][kc+1][nx[p][3]]+=w-(dp[u][kb][kc+1][nx[p][3]]+w>BASE)*BASE; 
   }
  forr(bk,ka-1,ka+1) forr(ck,ka-1,ka+1)
   if(ka+bk+ck==n && myabs(ka-bk)<=1 && myabs(ka-ck)<=1 && myabs(bk-ck)<=1 && bk>=0 && ck>=0) 
    forr(pp,1,m) if(w = dp[u][bk][ck][pp]) ans+=w-(ans+w>BASE)*BASE;
  u^=1;  
 }
 printf("%d",ans);
}
