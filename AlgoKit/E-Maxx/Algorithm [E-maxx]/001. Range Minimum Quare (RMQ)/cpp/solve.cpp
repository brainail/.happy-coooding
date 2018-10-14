#include<float.h>
#include<list>
#include<deque>
#include<stack>
#include<bitset>
#include<numeric>
#include<utility>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cfloat>
#include<algorithm>
#include<functional>
#include<iterator>
#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
#include<stdio.h>
#include<cmath>
#include<sstream>
#include<queue>
#include<set>
#include<map>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<(int)(y); i++)
#define _forr(i,y,x) for(int i=(int)(y); i>(int)(x); i--)
#define all(a) a.begin(), a.end()
#define _all(a) a.rbegin(), a.rend()
#define sz(x) x.size()
#define mem(a,b) memset(a,b,sizeof(a))
#define msg(x) cout << #x << " = " << x << endl;

const int Size=101000;
int n,f[Size][19],pw[19];

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 scanf("%d",&n);
 forr(i,0,n) scanf("%d",&f[i][0]);
 int lenSize=(int)(log(n+0.0)/log(2.0));
 pw[0]=1; 
 forr(i,1,lenSize+1) pw[i]=pw[i-1]*2;
 forr(len,1,lenSize+1) forr(i,0,n-pw[len]+1)
  f[i][len]=min(f[i][len-1],f[i+pw[len-1]][len-1]);
 int testcase; 
 scanf("%d",&testcase); 
 forr(i,0,testcase) {
  int l,r;
  scanf("%d %d",&l,&r);
  l--; r--;
  if(l>r) swap(l,r);
  int len=(int)(log(r-l+1.0)/log(2.0));
  printf("%d\n",min(f[l][len],f[r-pw[len]+1][len]));
 }
}

