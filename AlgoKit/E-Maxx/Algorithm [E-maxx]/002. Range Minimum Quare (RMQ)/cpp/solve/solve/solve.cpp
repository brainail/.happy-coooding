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

const int Size=1010000;
int n,a[Size],mL[Size],mR[Size],pw[20],f[Size/19][20];

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 scanf("%d",&n); 
 forr(i,1,n+1) scanf("%d",&a[i]);
 int lenSize=(int)(log(n+0.0)/log(2.0)),len;
 int k=(n/lenSize)+(n%lenSize>0),minL=a[1],minR=a[n],testcase,l,r;
 forr(i,1,n+1) { 
  minL=min(minL,a[i]); minR=min(minR,a[n-i+1]);
  mL[i]=minL; mR[n-i+1]=minR;
  if(i%lenSize==0) minL=a[i+1];
  if((n-i+1)%lenSize==1) minR=a[n-i];
 }
 pw[0]=1; 
 forr(i,1,lenSize+1) pw[i]=pw[i-1]*2;
 forr(i,1,k+1) f[i][0]=mR[(i-1)*lenSize+1];
 forr(len,1,lenSize+1) forr(i,1,k-pw[len]+2)
  f[i][len]=min(f[i][len-1],f[i+pw[len-1]][len-1]);
 scanf("%d",&testcase); 
 forr(i,0,testcase) {
  scanf("%d %d",&l,&r);
  if(l>r) swap(l,r);
  int ll=(l/lenSize)+(l%lenSize>0),rr=(r/lenSize)+(r%lenSize>0);
  if(ll==rr && l%lenSize==1) printf("%d\n",mL[r]); else
  if(ll==rr && r%lenSize==0) printf("%d\n",mR[l]); else
  if(ll==rr) { minL=a[l];
   forr(j,l,r+1) minL=min(minL,a[j]);
   printf("%d\n",minL);
  } else { ll++; rr--; minL=min(mL[r],mR[l]);
   int len;
   if(ll<=rr) len=(int)(log(rr-ll+1.0)/log(2.0));
   if(ll<=rr) minL=min(minL,min(f[ll][len],f[rr-pw[len]+1][len]));
   printf("%d\n",minL);
  }
 }
}

