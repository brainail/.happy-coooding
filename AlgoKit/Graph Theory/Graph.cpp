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

#define foreach(it, v, type) for( type::iterator it = v.begin(); it != v.end() ; it++)
#define forn(i, st, en) for(int i = (int)(st); i <= (int)(en); i++)
#define ford(i, en, st) for(int i = (int)(en); i >= (int)(st); i--)
#define zero(a, w) memset(a, w, sizeof(a))
#define all(a) a.begin(), a.end()
#define sz(a) a.size()

#define msg(x) cout << #x << " = " << x << endl;

// BEGIN CODE CUT HERE --- CLASS GRAPH

class graph {
 public:
  #define VSIZE 100 // The maximum number of vertices in the graph. Nodes are numbered from 0 to V-1.
  #define ESIZE 200 // The maximum number of edges in the graph. Edges are numbered from 0 to E-1.
  int V, E, last[VSIZE], next[ESIZE], to[ESIZE]; 
  
  graph() { V = 0, E = 0; }
  
  graph(const int m) {  
   assert(m-1 < VSIZE && m >= 0);
   V = m, E = 0;
   forn(i,0,V-1) last[i] = -1;
  }

  void resize(const int m) {  
   assert(m-1 < VSIZE && m >= 0);
   V = m, E = 0;
   forn(i,0,V-1) last[i] = -1;
  }

  void addEdge(const int x, const int y, const bool rev) { 
   assert(E < ESIZE && x >= 0 && x < V && y >= 0 && y < V);
   next[E] = last[x]; last[x] = E; to[E] = y; E++;
	 if(rev) addEdge(y, x, false);
  } 
 
  /* void addEdge(const int x, const int y, const int c, const bool rev) { 
   assert(E < ESIZE && x >= 0 && x < V && y >= 0 && y < V);
   next[E] = last[x]; last[x] = E; to[E] = y; cost[E] = c; E++;
	 if(rev) addEdge(y, x, c, false);
  } */
 
  /* void addEdgeFlow(const int x, const int y, const int cp, const bool rev) { 
   assert(E < ESIZE && x >= 0 && x < V && y >= 0 && y < V);
   next[E] = last[x]; last[x] = E; to[E] = y; cap[E] = cp; E++;
	 if(rev) addEdgeFlow(y, x, 0, false);
  } */
 
  /* void addEdgeFlow(const int x, const int y, const int c, const int cp, const bool rev) { 
   assert(E < ESIZE && x >= 0 && x < V && y >= 0 && y < V);
   next[E] = last[x]; last[x] = E; to[E] = y; cost[E] = c; cap[E] = cp; E++;
	 if(rev) addEdgeFlow(y, x, -c, 0, false);
  } */
  
  void print() {
   forn(v,0,V-1)
    for(int i = last[v]; i >= 0; i = next[i])
     printf("%d %d\n", v, to[i]);
  }
};

// END CODE CUT HERE --- CLASS GRAPH

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 graph g(17);
 g.resize(20);
 g.addEdge(0, 19, true);
 g.addEdge(4, 6, false);
 g.print();
}

