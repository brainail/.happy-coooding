#include <algorithm> // sort, lower_bound, min, max, next_permutation
#include <bitset>    // Sieve of Eratosthenes
#include <cmath>     // math routines: abs, pow...
#include <cstdio>    // In case needed
#include <cstdlib>
#include <ctype.h>   // char routines: isalpha...
#include <deque>
#include <iostream>  // io routines
#include <set>       // balanced BST (RB Tree) with key only
#include <map>       // balanced BST (RB Tree) for key-data pairs
#include <queue>     // queue & priority_queue
#include <stack>
#include <string>    // C++ class string
#include <vector>    // resizable array

using namespace std;

// common data types
typedef long long             ll;
typedef vector<int>           vi;
typedef pair<int, int>        ii;
typedef vector<ii>            vii;
typedef map<int, int>         mii;
typedef set<int>              si;
typedef map<string, int>      msi;
typedef vector<bool>          vb;
typedef long double           ld;

#define REP(i,a,b)  for (int i=int(a); i<int(b); i++)
#define REPN(i,n)   REP (i, 0, int(n))
#define REPD(i,a,b) for (int i=int(a); i>=int(b); i--)

#define TRvi(c, it)  \
  for (vi::iterator it = (c).begin(); it != (c).end(); it++)
#define TRvii(c, it) \
  for (vii::iterator it = (c).begin(); it != (c).end(); it++)
#define TRmsi(c, it) \
  for (msi::iterator it = (c).begin(); it != (c).end(); it++)

#define SIZE(c) (int((c).size()))
#define LOG(x) cerr << #x << " = " << x << endl;

// Avoid re-typing the test cases whenever you want to test your program
// Simply place test data inside "input.txt" and put this line just
// after int main()
#define REDIRECT_INPUT   freopen("input.txt", "r", stdin)

#define INF 2147483647 // 2^31-1
#define MEMSET_INF 127     // ~2B
#define MEMSET_HALF_INF 63 // ~1B
// useful to initialize shortest path distances, set INF to 127!
//memset(dist, MEMSET_INF, sizeof dist);
// useful to initialize DP memoization table
//memset(dp_memo, -1 sizeof dp_memo);
// useful to clear array of integers
//memset(arr, 0, sizeof arr);

// bit operations
#define isOn(i, bitmask)  (bitmask & (1 << i))
#define setOn(i, bitmask) (bitmask | (1 << i))

// Graph Library //
#define MAX_V 100         // Change this to the actual size of |V|
int AdjMat[MAX_V][MAX_V]; // if MAX_V > 100, consider using AdjList
vector<vii> AdjList;      // see vii shortcut above for explanation
priority_queue< pair<int, ii> > EdgeList;

// DFS
#define DFS_WHITE -1 // normal DFS, do not change this with other values (other than 0), because we usually use memset with conjunction with DFS_WHITE
#define DFS_BLACK 1
vi dfs_num;
int numComp;
void initDFS(int V) { // used in normal DFS
  dfs_num.assign(V, DFS_WHITE);
  numComp = 0;
}
#define DFS_GRAY 2 // one more color for graph edges property check
vi dfs_parent;
void initGraphCheck(int V) {
  initDFS(V);
  dfs_parent.assign(V, 0);
}
vi dfs_low; // additional information for articulation points/bridges
vb articulation_vertex;
int dfsNumberCounter, dfsRoot, rootChildren;
void initArticulationPointBridge(int V) {
  initGraphCheck(V);
  dfs_low.assign(V, 0);
  articulation_vertex.assign(V, false);
  dfsNumberCounter = 0;
}
stack<int> dfs_scc; // additional information for SCC
void initTarjanSCC(int V) {
  initGraphCheck(V);
  dfs_low.assign(V, 0);
  dfsNumberCounter = 0;
  numComp = 0;
  while (!dfs_scc.empty())
    dfs_scc.pop();
}
vi topologicalSort; // additional information for toposort
void initTopologicalSort(int V) {
  initDFS(V);
  topologicalSort.clear();
}

// Union-Find Disjoint Sets Library //
// NB: does not include the `union by rank' heuristic yet
// 1000 is just a rough number, adjustable by user
vi pset(1000), set_size(1000); int disjointSetsSize;
void initSet(int N) { disjointSetsSize = N; set_size.assign(N, 1); pset.assign(N, 0); REP (i, 0, N - 1) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { if (!isSameSet(i, j)) { disjointSetsSize--; set_size[findSet(j)] += set_size[findSet(i)]; pset[findSet(i)] = findSet(j); } }
int numDisjointSets() { return disjointSetsSize; }
int sizeOfSet(int i) { return set_size[findSet(i)]; }

// Segment Tree Library //
// The segment tree is stored like a heap array
void st_build(vi &t, const vi &A, int node, int b, int e) {
  if (b == e) // as b == e, either one is fine
    t[node] = b; // store the index
  else { // recursively compute the values in the left and right subtrees
    int lIdx = 2 * node, rIdx = 2 * node + 1;
    st_build(t, A, lIdx, b              , (b + e) / 2);
    st_build(t, A, rIdx, (b + e) / 2 + 1, e          );
    int lContent = t[lIdx]    , rContent = t[rIdx];
    int lValue   = A[lContent], rValue   = A[rContent];
    t[node] = (lValue <= rValue) ? lContent : rContent;
} }
vi st_create(const vi &A) { // if original array size is N,
  // the required segment tree array length is 2*2^(floor(log2(N)) + 1);
  int l = (int)(2 * pow(2.0, floor((log((double)A.size()) / log(2.0)) + 1)));
  vi t(l, 0); // create vector with length l and fill it with 0es
  st_build(t, A, 1, 0, (int)A.size() - 1); // recursively build the segment tree
  return t;
}
int st_rmq(vi &t, const vi &A, int node, int b, int e, int i, int j) {
  if (i >  e || j <  b) return -1; // if current segment completly outside query segment
  if (b >= i && e <= j) return t[node]; // if current segment is inside query segment
  // compute the min position in the left and right part of the interval
  int p1 = st_rmq(t, A, 2 * node    , b              , (b + e) / 2, i, j);
  int p2 = st_rmq(t, A, 2 * node + 1, (b + e) / 2 + 1, e          , i, j);
  // return the position where the overall minimum is
  if (p1 == -1) return p2; // can happen if we try to access segment outside query
  if (p2 == -1) return p1; // same as above
  return (A[p1] <= A[p2]) ? p1 : p2;
}
int st_rmq(vi &t, const vi& A, int i, int j) { // overloading, simplified parameters
  return st_rmq(t, A, 1, 0, (int)A.size() - 1, i, j);
}
int st_update_point(vi &t, vi &A, int node, int b, int e, int idx, int new_value) {
  // this update code is still preliminary, i == j
  // must be able to update range in the future!
  int i = idx, j = idx;
  // if the current interval does not intersect 
  // the update interval, return this st node value!
  if (i > e || j < b)
    return t[node];
  // if the current interval is included in the update range,
  // update that st[node]
  if (b == i && e == j) {
    A[i] = new_value; // update the underlying array
    return t[node] = b; // this index
  }
  // compute the minimum position in the 
  // left and right part of the interval
  int p1, p2;
  p1 = st_update_point(t, A, 2 * node    , b              , (b + e) / 2, idx, new_value);
  p2 = st_update_point(t, A, 2 * node + 1, (b + e) / 2 + 1, e          , idx, new_value);
  // return the position where the overall minimum is
  return t[node] = (A[p1] <= A[p2]) ? p1 : p2;
}
int st_update_point(vi &t, vi &A, int idx, int new_value) {
  return st_update_point(t, A, 1, 0, (int)A.size() - 1, idx, new_value);
}

// Fenwick Tree Library //
// The Fenwick tree is stored as an array (vector)
vi ft;
vi ft_create(int n) { return vi(n, 0); } // initially n elements, all zeroes.
int ft_rsq(const vi &t, int a, int b) {  // returns RSQ(a, b)
  if (a == 0) { int sum = 0; for (; b >= 0; b = (b & (b + 1)) - 1) sum += t[b]; return sum; }
  else return ft_rsq(t, 0, b) - ft_rsq(t, 0, a - 1);
}
// adjusts value of the k-th element by v (v can be positive/increase or negative/decrease).
void ft_adjust(vi &t, int k, int v) { for (; k < (int)t.size(); k |= k + 1) t[k] += v; }

// Mathematics Library //
ll _sieve_size;
bitset<10000010> bs; // 10^7 should be enough for most cases
vi primes; // compact list of primes in form of vector<int>

void sieve(ll upperbound) { // create list of primes in [0 .. upperbound]
  _sieve_size = upperbound + 1; // add 1 to include upperbound
  bs.reset(); bs.flip(); // set all numbers to 1
  bs.set(0, false); bs.set(1, false); // except index 0 and 1
  for (ll i = 2; i <= _sieve_size; i++) if (bs.test((size_t)i)) {
    // cross out multiples of i starting from i * i!
    for (ll j = i * i; j <= _sieve_size; j += i) bs.set((size_t)j, false);
    primes.push_back((int)i); // simultaneously update this
  }
} // call this method in main method

bool isPrime(ll N) { // a good deterministic prime tester
  if (N < _sieve_size) return bs.test((size_t)N); // O(1) for small primes
  REP (i, 0, primes.size() - 1) if (N % primes[i] == 0) return false;
  return true; // it takes longer time if N is a large prime!
} // Note: only work for N <= (last prime in vi "primes")^2

mii primeFactors(int N) { // returns prime-power factorization of N in a map<int, int>
  mii factors;  // vi "primes" (generated by sieve) is optional
  int PF_idx = 0, PF = primes[PF_idx]; // using PF = 2, 3, 4, ..., is also ok.
  while (N != 1 && ((ll)PF * PF <= N)) { // stop at sqrt(N), but N can get smaller, be careful of overflow
    while (N % PF == 0) { N /= PF; factors[PF]++; } // remove this PF, increase count
    PF = primes[++PF_idx]; // only consider primes!
  }
  if (N != 1) factors[N]++; // special case if N is actually a prime
  return factors;
}

int EulerPhi(int N) {
  mii factors = primeFactors(N);
  int result = N;
  for (mii::iterator i = factors.begin(); i != factors.end(); i++)
    result = result - result / i->first;
  return result;
}

int gcd(int a, int b) { return (b == 0 ? a : gcd(b, a % b)); }
int lcm(int a, int b) { return (a * b / gcd(a, b)); }

pair<ii, int> extendedEuclid(int a, int b) {
  if (b == 0)
    return make_pair(make_pair(1, 0), a);
  pair<ii, int> result = extendedEuclid(b, a % b);
  int x = result.first.first, y = result.first.second;
  int d = result.second;
  int x1 = y;
  int y1 = x - (a / b) * y;
  x = x1;
  y = y1;
  return make_pair(make_pair(x, y), d);
}
