#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>

#include <numeric>
#include <iomanip>
#include <complex>
#include <float.h>
#include <cfloat>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdio>

#include <cstring>
#include <string>

#include <iterator>
#include <vector>
#include <bitset>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
using namespace std;

#define forn(i, st, en) for(int i = (int)(st); i <= (int)(en); i++)
#define zero(a, w) memset(a, w, sizeof(a))

// BEGIN CODE CUT HERE --- CLASS FLOW

class flow {
public:
 #define VSIZE 5010 // The maximum number of vertices in the graph. Nodes are numbered from 0 to V-1.
 #define ESIZE 60010 // The maximum number of edges in the graph. Edges are numbered from 0 to E-1.
 typedef int Tf; // Type of flow: a integer or fractional
 long long coutFlow; // If the answer requires more then change the type  
 static const Tf INF = 1000000000;
 int last[VSIZE], next[ESIZE], to[ESIZE], last2[VSIZE], dist[VSIZE], q[VSIZE], S, T, V, E;
 Tf cap[ESIZE];

 flow() { V = 0, E = 0; }

 flow(const int m) {  
  assert(m-1 < VSIZE && m >= 0);
  V = m, E = 0;
  forn(i,0,V-1) last[i] = -1;
 }

 inline void resize(const int m) {  
  assert(m-1 < VSIZE && m >= 0);
  V = m, E = 0;
  forn(i,0,V-1) last[i] = -1;
 }  

 void addEdge(const int x, const int y, const Tf cp, const bool rev) { 
  assert(E < ESIZE && x >= 0 && x < V && y >= 0 && y < V);
  next[E] = last[x]; last[x] = E; to[E] = y; cap[E++] = cp; 
  if(rev) addEdge(y, x, 0, false);
 } 

 Tf dfsFlow(int v, Tf toCap) {
  if(v == T || toCap == 0) return toCap;
  for(int &i = last[v]; i >= 0; i = next[i]) 
   if(cap[i] > 0 && dist[v] + 1 == dist[to[i]]) {
    int canFlow = dfsFlow(to[i], min(cap[i], toCap));
    if(canFlow > 0) { 
     cap[i] -= canFlow, cap[i^1] += canFlow; 
     return canFlow;
    }
   }
   return 0;
 }  

 inline bool bfsFlow() {
  forn(i,0,V-1) { last[i] = last2[i]; dist[i] = -1; }
  int cq = 0, nq = 1; q[0] = S, dist[S] = 0;
  while(cq < nq) {
   int v = q[cq++];
   for(int i = last[v]; i >= 0; i = next[i])
    if(cap[i] > 0 && dist[to[i]] == -1) { dist[to[i]] = dist[v] + 1, q[nq++] = to[i]; }
  }
  return dist[T] != -1;
 }

 inline long long maxFlow(const int SS, const int TT) {
  S = SS, T = TT, coutFlow = 0;
  forn(i,0,V-1) last2[i] = last[i];
  while(bfsFlow()) 
   while(Tf FLOW = dfsFlow(S, INF)) coutFlow += FLOW;  
  return coutFlow;
 } 
};

// BEGIN CODE CUT HERE --- CLASS FLOW

char input[2000000];
char* curPos;

int nextInt()
{
 while (!isdigit(*curPos)) curPos++;

 int res = 0;
 while (isdigit(*curPos)) 
 {
  res = res * 10 + (*curPos) - '0';
  curPos++;

 }
 return res;
}

flow web;

int main()
{
 int sz = fread(input, 1, sizeof(input), stdin);
 curPos = input;

 int m = nextInt();
 int n = nextInt();
 
 web.resize(m);

 forn(i,1,n) {
  int x = nextInt();
  int y = nextInt();
  int z = nextInt();

  web.addEdge(x-1, y-1, z, false);
  web.addEdge(y-1, x-1, z, false);
 }

 long long ans = web.maxFlow(0, m-1);

 cout << ans;
}
