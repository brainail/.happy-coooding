#include<cassert>
#include<iostream>
#include<stdio.h>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int n,col,ans=0;
bool p[1010];

int main() {
 scanf("%d %d",&n,&col);
 assert(n >= 2 && n <= 1000);
 assert(col >= 0 && col <= 1000);
 forr(i,0,n+1) p[i] = true;
 // FInd prime number 
 p[1] = p[0] = false;
 for(int i = 2; i * i <= n; i++) if(p[i])
   for(int j = i * i; j <= n; j+=i) p[j] = false;
 // Find Nol'dbax number
 forr(i,2,n) if(p[i])
  forr(j,i+1,n) if(p[j]) {
   if(i+j+1 <= n && p[i+j+1]) ans ++;
   break;
  }  
 if(ans >= col ? printf("YES") : printf("NO"));
 return 0;
}
