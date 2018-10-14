#include<cassert>
#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)
#define sz(x) x.size()

const int vSIZE = 1010;
const int Inf = 1000000000;

int m,n,x,y,c,q[vSIZE],d[vSIZE],s[vSIZE],ans=0,v=-1;
bool was[vSIZE];
vector< vector<int> > go;

void dfs(int u) {
 was[u] = true;
 forr(i,0,sz(go[u])-1) {
  assert(!was[go[u][i]]);
  dfs(go[u][i]);
 }
}

int main() {
 scanf("%d",&m);
 assert(m >= 1 && m <= 1000);
 forr(i,1,m) {
  scanf("%d",&q[i]);
  assert(q[i] <= 1000000 && q[i] >= 0);
 }
 scanf("%d",&n);
 assert(n >= 0 && n <= 10000);
 forr(i,1,m) { d[i] = Inf; s[i] = -1; }
 forr(i,1,n) {
  scanf("%d %d %d",&x,&y,&c);
  assert(x >= 1 && x <= m);
  assert(y >= 1 && y <= m);
  assert(c >= 0 && c <= 1000000);
  assert(q[x] > q[y]);
  if(c < d[y]) { d[y] = c; s[y] = x; }
 }
 go.clear(); go.resize(m+1);
 forr(i,1,m) if(s[i] != -1) {
  ans += d[i];
  go[s[i]].push_back(i);
 } else {
  if(v != -1) { printf("-1"); return 0; }
  v = i;
 }
 forr(i,1,m) was[i] = false;
 dfs(v);
 forr(i,1,m) assert(was[i]);
 printf("%d",ans);
}
