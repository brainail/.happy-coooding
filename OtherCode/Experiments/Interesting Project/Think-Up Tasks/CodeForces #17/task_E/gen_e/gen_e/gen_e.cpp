#include "testlib.h"
#include <iostream>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int p[30];
char a[2000010];

// 0 - standart 
// 1 - 1 2 1 2 1 2
// 3 - 1 1 1 1 ... 2 1 1 1 ...

int main(int argc, char* argv[]) {
 registerGen(argc, argv);

 int n = atoi(argv[1]);
 p[1] = atoi(argv[2]);
 p[2] = atoi(argv[3]);
 p[3] = atoi(argv[4]);
 
 int ostP = 100 - p[1] - p[2] - p[3];
 forr(i,4,26) {
  p[i] = rnd.next(0, ostP);
  ostP -= p[i];
 }
 
 if(argv[5][0] == '0') {
  string token = "[";
  forr(i,0,25)
   forr(j,1,p[i+1]) 
    token = token + (char)(i + 'a'); 
  token = token + ']';
  token = token + "{" + argv[1] + "," + argv[1] + "}";
  string ans = rnd.next(token);
  printf("%d\n",n);
  forr(i,0,n-1) printf("%c",ans[i]);
  printf("\n");
 } else 
 if(argv[5][0] == '1') {
  int len[2];
  string s[2];
  len[0] = rnd.next(1, 3);
  len[1] = rnd.next(1, 3);
  s[0] = s[1] = "";
  forr(i,1,len[0]) s[0] = s[0] + (char)(rnd.next(0,2) + 'a');
  forr(i,1,len[1]) s[1] = s[1] + (char)(rnd.next(0,2) + 'a');
  printf("%d\n",n);
  int x = 0;
  while(n) {
   forr(i,0,min(n,len[x])-1) printf("%c",s[x][i]);
   n -= min(n, len[x]);
   x ^= 1;
  }
  printf("\n");
 } else {
  printf("%d\n",n);
  long long m = n;
  m = (m * (m+1)) / 2;
  long long k = 0;
  long long t = rnd.next((long long)0, m);
  forr(i,1,n) a[i] = 'a';
  forr(i,1,n) 
   if(t > i) t -= i; else { k += i / 7; a[i] = 'b'; t += i + k; }
  forr(i,1,n) printf("%c",a[i]); 
  printf("\n");
 }
 
 return 0;
}
