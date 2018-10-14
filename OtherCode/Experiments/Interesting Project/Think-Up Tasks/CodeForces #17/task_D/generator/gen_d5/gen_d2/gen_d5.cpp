#include "testlib.h"
#include <iostream>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)
#define _forr(i,y,x) for(int i=(int)(y); i>=(int)(x); i--)

const int Size = 2000010;

int B[Size],T[Size],H[Size],A[Size],nt = 0;

int main(int argc, char* argv[]) {
 registerGen(argc, argv);
 int n = atoi(argv[1]);
 int step = atoi(argv[2]);
 int C = rnd.next(1000000000 / step);
 C *= step;
 
 int m = C, phi = C;
 for(int i = 2; i * i <= C; i++)
  if(m % i == 0) {
   while(m % i == 0) m /= i;
   phi -= phi / i;
  }
 if(m > 1) phi -= phi / m;
 
 B[n] = rnd.next(2, 9);
 _forr(i,n-1,1) B[i] = rnd.next(0, 9);
 
 int x = phi;
 while(x) {
  nt ++;
  T[nt] = x % 10;
  x = x / 10;
 }
 forr(i,0,Size-1) H[i] = 0;
 
 forr(i,1,n) 
  forr(j,1,nt) 
   H[i+j-1] += B[i] * T[j];
   
 int len = nt + n + 3;
 forr(i,1,len)
  if(H[i] >= 10) {
   H[i+1] += H[i] / 10;
   H[i] %= 10;
  }
 
 while(len>1 && !H[len]) len--;
 H[1] += 0;
 len ++;
 forr(i,1,len)
  if(H[i] >= 10) {
   H[i+1] += H[i] / 10;
   H[i] %= 10;
  }
 while(len>1 && !H[len]) len--;
 forr(i,1,len) B[i] = H[i];
 int lenB = len;
 
 ////////////////////////////
 
 n += 5;
 forr(i,0,Size-1) A[i] = 0;
 A[n] = rnd.next(2, 9);
 _forr(i,n-1,1) A[i] = rnd.next(0, 9);
 
 x = C; nt = 0;
 while(x) {
     nt ++;
     T[nt] = x % 10;
     x = x / 10;
 }
 forr(i,0,Size-1) H[i] = 0;

 forr(i,1,n) 
  forr(j,1,nt) 
   H[i+j-1] += A[i] * T[j];

 len = nt + n + 3;
 forr(i,1,len)
  if(H[i] >= 10) {
   H[i+1] += H[i] / 10;
   H[i] %= 10;
  }
 while(len>1 && !H[len]) len--;
 forr(i,1,len) A[i] = H[i];
 int lenA = len;
 
 _forr(i,lenA,1) printf("%d",A[i]);
 printf(" ");
 _forr(i,lenB,1) printf("%d",B[i]);
 printf(" ");
 printf("%d",C);
 printf("\n");
 return 0;
}
