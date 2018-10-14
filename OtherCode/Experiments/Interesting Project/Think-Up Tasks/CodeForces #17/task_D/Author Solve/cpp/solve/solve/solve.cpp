#include<cassert>
#include<iostream>
#include<stdio.h>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)
#define _forr(i,y,x) for(int i=(int)(y); i>=(int)(x); i--)

const int SIZE = 1000010;

struct Tlong { int n; short a[SIZE]; };

Tlong b, p; 

int main() {
 char ch = getchar();
 b.n = 0;
 while(ch >= '0' && ch <= '9') {
  b.a[b.n ++] = ch - '0';
  ch = getchar();
 }
 ch = getchar();
 p.n = 0;
 while(ch >= '0' && ch <= '9') {
  p.a[p.n ++] = ch - '0';
  ch = getchar();
 }
 int BASE;
 scanf("%d",&BASE);
 
 // Find phi number
 int n = BASE, phi = BASE, pow = 0;
 for(int i = 2; i * i <= BASE; i++)
  if(n % i == 0) {
   while(n % i == 0) n /= i;
   phi -= phi / i;
  }
 if(n > 1) phi -= phi / n;
  
 // P --
 p.a[p.n-1] --;
 _forr(i,p.n-1,0)  
  if(p.a[i] < 0) { p.a[i] += 10; p.a[i-1] --; }
  
 // If Step not big -> brute pow = p
 if(p.n < 7) {
  forr(i,0,p.n-1) pow = pow * 10 + p.a[i];
 } else {

  // p % phi (p > log2(c))
  for(int i=(!p.a[0]); i<p.n; i++) pow = ((long long)pow * 10 + p.a[i]) % phi;
  while(pow < 50) pow += phi;
 }
 
 // B^pow % BASE = (B % BASE)^pow % BASE
 int wb = 0, res = 1;
 forr(i,0,b.n-1) wb = ((long long)wb * 10 + b.a[i]) % BASE;
 
 while(pow) 
  if(pow % 2) {
   res = ((long long)res * wb) % BASE;
   pow --;
  } else {
   wb = ((long long)wb * wb) % BASE;
   pow /= 2;
  }
 
 // B --
 b.a[b.n-1] --;
 _forr(i,b.n-1,0)  
  if(b.a[i] < 0) { b.a[i] += 10; b.a[i-1] --; }
   
 // B % BASE
 wb = 0;
 for(int i=(!b.a[0]); i<b.n; i++) wb = ((long long)wb * 10 + b.a[i]) % BASE; 
 
 res = ((long long)res * wb) % BASE;
 
 if(!res) res = BASE;
 printf("%d",res);
}

