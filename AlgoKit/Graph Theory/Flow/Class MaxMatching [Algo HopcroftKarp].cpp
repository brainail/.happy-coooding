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
  #define VSIZE 100 // The maximum number of vertices in the graph [G1 + G2]. Nodes are numbered G1[1 to V1], G2[V1+1 to V1+V2]
  #define ESIZE 200 // The maximum number of edges in the graph. Edges are numbered from 0 to E-1.
  #define NIL 0 // Is a special null vertex
  #define INF 1000000000
  int last[VSIZE], next[ESIZE], to[ESIZE], pred[VSIZE], dist[VSIZE], q[VSIZE], Va, Vb, E;
  bool used[VSIZE];

  matching() { Va = 0, Vb = 0, E = 0; }

  matching(const int m, const int n) {
   assert(m + n < VSIZE && m >= 0 && n >= 0);
   Va = m, Vb = n, E = 0;
   forn(i,0,Va+Vb) last[i] = -1;
  }

  inline void resize(const int m, const int n) {
   assert(m + n < VSIZE && m >= 0 && n >= 0);
   Va = m, Vb = n, E = 0;
   forn(i,0,Va+Vb) last[i] = -1;
  }

  inline void addEdge(const int x, const int y) {
   assert(E < ESIZE && x > 0 && x <= Va && y > 0 && y <= Vb && Va + y < VSIZE);
   next[E] = last[x]; last[x] = E; to[E++] = Va + y;
  }

  inline bool bfs() {
   int cq = 0, nq = 0;
   forn(i,1,Va)
    if(pred[i] == NIL) {
     dist[i] = 0, q[nq++] = i;
    } else dist[i] = INF;
   dist[NIL] = INF;
   while(cq < nq) {
    int v = q[cq++];
    if(v != NIL)
     for(int i = last[v]; i >= 0; i = next[i])
      if(dist[pred[to[i]]] == INF) {
       dist[pred[to[i]]] = dist[v] + 1, q[nq++] = pred[to[i]];
      }
   }
   return dist[NIL] != INF;
  }

  bool HopcroftKarp(int v) {
   if(v != NIL) {
    for(int i = last[v]; i >= 0; i = next[i])
     if(dist[pred[to[i]]] == dist[v] + 1)
      if(HopcroftKarp(pred[to[i]])) {
       pred[to[i]] = v, pred[v] = to[i];
       return true;
      }
    dist[v] = INF;
    return false;
   }
   return true;
  }

  inline int maxMatchings() {
   forn(i,0,Va+Vb) pred[i] = NIL;
   int coutMaxMatchings = 0;
   while(bfs())
    forn(i,1,Va)
     if(pred[i] == NIL)
      if(HopcroftKarp(i)) coutMaxMatchings ++;
   return coutMaxMatchings;
  }
};

// BEGIN CODE CUT HERE --- CLASS MATCHING

int n, m, p;
matching web;

int main() {
 /* freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout); */
 scanf("%d %d %d",&m, &n, &p);
 web.resize(m, n);
 forn(i,1,p) {
  int x, y;
  scanf("%d %d",&x, &y);
  web.addEdge(x, y);
 }
 int ans = web.maxMatchings();
 printf("%d",ans);
}
