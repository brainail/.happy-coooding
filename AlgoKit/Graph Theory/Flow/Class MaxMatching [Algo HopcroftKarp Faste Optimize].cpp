#include <cassert>

#include <iostream>
#include <stdio.h>

#include <cstring>
using namespace std;

#define forn(i, st, en) for(int i = (int)(st); i <= (int)(en); i++)
#define zero(a, w) memset(a, w, sizeof(a))

// BEGIN CODE CUT HERE --- CLASS MATCHING

class matching {
 public:
  #define VSIZE1 50010 // The maximum number of vertices in the graph G1. Nodes are numbered from 0 to V1-1.
  #define VSIZE2 50010 // The maximum number of vertices in the graph G2. Nodes are numbered from 0 to V2-1.
  #define ESIZE 150010 // The maximum number of edges in the graph. Edges are numbered from 0 to E-1.
  int V1, V2, E, last[VSIZE1], next[ESIZE], to[ESIZE], p1[VSIZE1], p2[VSIZE2], used[VSIZE2], rMatch, lev[VSIZE1], q[VSIZE1], *qb, *qe;
  
  matching() { V1 = 0, V2 = 0, E = 0; }

  matching(const int m, const int n) {  
   assert(m-1 < VSIZE1 && m >= 0 && n-1 < VSIZE2 && n >= 0);
   V1 = m, V2 = n, E = 0;
   forn(i,0,V1-1) last[i] = ~0;
  }
  
  inline void resize(const int m, const int n) {  
   assert(m-1 < VSIZE1 && m >= 0 && n-1 < VSIZE2 && n >= 0);
   V1 = m, V2 = n, E = 0;
   forn(i,0,V1-1) last[i] = ~0;
  }  

  inline void addEdge(const int x, const int y) { 
   assert(E < ESIZE && x >= 0 && x < V1 && y >= 0 && y <= V2);
   next[E] = last[x]; last[x] = E; to[E++] = y;
  } 
  
  bool hopk(int u) { 
   int v, w, i; 
   used[u] = rMatch; 
   for(i = last[u]; ~i; i = next[i]) 
    if (!~(w = p2[v = to[i]]) || used[w] != rMatch && lev[u] < lev[w] && hopk(w)) { p1[u] = v, p2[v] = u; return 1; } 
   return 0; 
  } 

  inline int maxMatching() { 
   int f, u, w; 
   forn(i,0,(V1>V2)?V1:V2) p1[i] = p2[i] = used[i] = ~0;
   for(rMatch = 0; ; rMatch += f) { 
    qb = qe = q; 
    forn(i,0,V1-1) lev[i] = ~0;
    for(u = 0; u < V1; u++) if(!~p1[u]) lev[*qe++ = u] = 0; 
    for(; qb != qe; ) for(int i = last[u = *qb++]; ~i; i = next[i]) if(~(w = p2[to[i]]) && !~lev[w]) lev[*qe++ = w] = lev[u] + 1;
    for(f = 0, u = 0; u < V1; ++u) if(!~p1[u]) f += hopk(u); 
    if(!f) return rMatch; 
   } 
  } 
}; 

// BEGIN CODE CUT HERE --- CLASS MATCHING

int n, m, p;
matching web;

int main() {
 /* freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout); */ 
 web.resize(m, n);

 forn(i,1,p)
 {
  web.addEdge(x, y);
 }

 int ans = web.maxMatching();
 printf("%d",ans);
}
