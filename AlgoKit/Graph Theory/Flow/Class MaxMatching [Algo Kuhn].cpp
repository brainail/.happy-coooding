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

// BEGIN CODE CUT HERE --- CLASS MATCHING

class matching {
 public:
  #define VSIZE1 50010 // The maximum number of vertices in the graph G1. Nodes are numbered from 0 to V1-1.
  #define VSIZE2 50010 // The maximum number of vertices in the graph G2. Nodes are numbered from 0 to V2-1.
  #define ESIZE 150010 // The maximum number of edges in the graph. Edges are numbered from 0 to E-1.
  int last[VSIZE1], next[ESIZE], to[ESIZE], p2[VSIZE2], p1[VSIZE1], V1, V2, E;
  bool used[VSIZE1];

  matching() { V1 = 0, V2 = 0, E = 0; }

  matching(const int m, const int n) {  
   assert(m-1 < VSIZE1 && m >= 0 && n-1 < VSIZE2 && n >= 0);
   V1 = m, V2 = n, E = 0;
   forn(i,0,V1-1) last[i] = -1;
  }

  inline void resize(const int m, const int n) {  
   assert(m-1 < VSIZE1 && m >= 0 && n-1 < VSIZE2 && n >= 0);
   V1 = m, V2 = n, E = 0;
   forn(i,0,V1-1) last[i] = -1;
  }  

  inline void addEdge(const int x, const int y) { 
   assert(E < ESIZE && x >= 0 && x < V1 && y >= 0 && y < V2);
   next[E] = last[x]; last[x] = E; to[E++] = y; 
  } 

  bool kuhn(int v) {
   if(used[v]) return false;
   used[v] = true;
   for(int i = last[v]; i >= 0; i = next[i])
    if(p2[to[i]] == -1 || kuhn(p2[to[i]])) {
     p2[to[i]] = v;
     p1[v] = to[i];
     return true;
    }                      
    return false;
  }

  inline int maxMatchings() {
   forn(i,0,V1-1) p1[i] = -1; 
   forn(i,0,V2-1) p2[i] = -1; 
   int coutMaxMatchings = 0, oldCoutMaxMatchings = -1;
   while(coutMaxMatchings != oldCoutMaxMatchings) {
    oldCoutMaxMatchings = coutMaxMatchings;
    memset(used, 0, V1);
    forn(i,0,V1-1)
     if(!used[i] && last[i] != -1 && p1[i] == -1 && kuhn(i)) coutMaxMatchings ++;
   }
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
 web.resize(max(m, n));
 forn(i,1,p) {
  int x, y;
  scanf("%d %d",&x, &y);
  web.addEdge(x-1, y-1);
 }
 int ans = web.maxMatchings();
 printf("%d",ans);
}
