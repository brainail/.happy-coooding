#include "testlib.h"
#include <iostream>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

bool p[1010];

int main(int argc, char* argv[]) {
 registerGen(argc, argv);
 int left = atoi(argv[1]);
 int right = atoi(argv[2]);
 int n = rnd.next(left, right);
 
 forr(i,0,n+1) p[i] = true;
 // FInd prime number 
 p[1] = p[0] = false;
 for(int i = 2; i * i <= n; i++) if(p[i])
  for(int j = i * i; j <= n; j+=i) p[j] = false;
 // Find Nol'dbax number
 int ans = 0;
 forr(i,2,n) if(p[i])
  forr(j,i+1,n) if(p[j]) {
   if(i+j+1 <= n && p[i+j+1]) ans ++;
   break;
 }  
 
 if(argv[3][0] == '0') {
  ans += 2;
  if(ans > 1000) ans = 1000;
 } 
 cout << n << " " << ans << endl;
 return 0;
}
