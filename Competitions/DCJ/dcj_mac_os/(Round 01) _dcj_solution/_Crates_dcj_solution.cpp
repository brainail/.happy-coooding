#include <message.h>
#include "crates.h"
// #include "_dcj_solution.h"

// #define __INCLUDE_MANUAL
#ifndef __INCLUDE_MANUAL
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
#endif

// TYPEDEFS
typedef long long tll;
typedef long double tld;
typedef unsigned long tul;
typedef pair < int, int > tpii;
typedef pair < string, string > tpss;
typedef vector < pair < int, int > > tvpii;
typedef vector < pair < string, string > > tvpss;
typedef vector < int > tvi;
typedef vector < string > tvs;
typedef vector < long long > tvll;
typedef vector < long double > tvld;

// DEFINES
#define forn(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define fordn(index, end, start) for (int index = (int) (end); index >= (int) (start); -- index)
#define _forn(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define _fordn(index, end, start) for (int index = (int) (end); index > (int) (start); -- index)
#define sforn(index, start, end, shift) for (int index = (int) (start); index <= (int) (end); index += shift)
#define sfordn(index, end, start, shift) for (int index = (int) (end); index >= (int) (start); index -= shift)
#define _sforn(index, start, end, shift) for (int index = (int) (start); index < (int) (end); index += shift)
#define _sfordn(index, end, start, shift) for (int index = (int) (end); index > (int) (start); index -= shift)
#define forIt(itIndex, container) for (typeof(container.begin()) itIndex = container.begin(); itIndex != container.end(); ++ itIndex)
#define forT(testId) int __T; scanf("%d\n", &__T); _forn(testId, 0, __T)
#define fill(box, value) memset(box, value, sizeof(box))
#define fill0(box) memset(box, 0, sizeof(box))
#define fillf(box) memset(box, false, sizeof(box))
#define fill_(box) memset(box, -1, sizeof(box))
#define all(box) box.begin(), box.end()
#define rall(box) box.rbegin(), box.rend()
#define csize(box) ((int) (box.size()))
#define clen(box) ((int) (box.length()))
#define mp(firstItem, secondItem) make_pair(firstItem, secondItem)
#define pb(value) push_back(value)
#define pw2(power) (1 << (power))
#define pw2l(power) (((LL) (1)) << (power))
#define hasBit(mask, index) (((mask) & pw2(index)) != 0)
#define hasBitl(mask, index) (((mask) & pw2l(index)) != 0)
#define calcBits(value) (__builtin_popcount(value))
#define allMasks(maskIndex, length) for (int maskIndex = 0; maskIndex < TWOP(length); ++ maskIndex)
#define allSubmasks(maskIndex, mask) for (int maskIndex = mask; ; maskIndex = ((maskIndex - 1) & mask))
#define contain(container, key) (container.find(key) != container.end())
#define debug(who) cout << #who << " = " << who << endl;
#define debug2(who, who2) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl;
#define debug3(who, who2, who3) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl;
#define debugp(who) cout << #who << " = (" << who.first << ", " << who.second << ")" << endl;
// #define endl '\n'

// CONSTS
const tld PI = acos(-1.0);
const tld EPS = 1e-9;
const int INF = 1000000000;
const tll INFL = (tll) 1000000000 * (tll) 1000000000;
const int NULO = -1;

// TEMPLATES
template<class T> inline int cmpf(T X, T Y = 0, T EPS_DIST = EPS) { return (X <= Y + EPS_DIST) ? ((X + EPS_DIST < Y) ? -1 : 0) : +1; }
template<class T> inline T gcd(T A, T B) { return (A < 0) ? gcd(-A, B) : ((B < 0) ? gcd(A, -B) : ((0 == B) ? A : gcd(B, A % B))); }
template<class T> inline T lcm(T A, T B) { return (A < 0) ? lcm(-A, B) : ((B < 0) ? lcm(A, -B) : (A * (B / gcd(A, B)))); }
template<class T> inline string tos(T X) { ostringstream oss; oss << X; oss.flush(); return oss.str(); }
template<class T> inline void fmin(T & B, T A) { if (A < B) B = A; }
template<class T> inline void fmax(T & B, T A) { if (A > B) B = A; }
template<class T> inline T sqr(T X) { return X * X; }

// INLINES
inline bool isUpper(char C) { return C >= 'A' && C <= 'Z'; }
inline bool isLower(char C) { return C >= 'a' && C <= 'z'; }
inline bool isLetter(char C) { return isUpper(C) || isLower(C); }
inline int toI(char C) { return isUpper(C) ? (int) (C - 'A') : (isLower(C) ? (int) (C - 'a') : -1); }
inline bool isDigit(char C) { return C >= '0' && C <= '9'; }
inline char toLower(char C) { return (char) ((isUpper(C)) ? (C + 32) : C); }
inline char toUpper(char C) { return (char) ((isLower(C)) ? (C - 32) : C); }
inline int toInt(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline double toF(string S) { double value; istringstream iss(S); iss >> value; return value; }
inline string deletews(string buffData) { buffData.erase(std::remove(all(buffData), ' '), buffData.end()); return buffData; }

// MY
vector<tll> h;
vector<tll> hupl;
// set< pair<tll, int> > hset;
tll htotal = 0;
tll rtv;
tll MODULO; // const
int n;
int rlb;

inline tll getUpl(int i) {
  tll leftmost = htotal % n;
  tll ch = htotal / n;
  if (i < leftmost) {
    if (htotal % n) ++ ch;
    return ch;
  }
  return ch;
}

inline void incRtv(tll x) {
  if (x > MODULO) x %= MODULO;
  rtv = (rtv + x) % MODULO;
}

int main() {
  // Common
  // ↓↓↓↓↓↓
  int nodes = NumberOfNodes();
  int me = MyNodeId();

  // If you don't want to use communication (for small inputs)
  // if (me != 0) {
    // return 0;
  // }

  // Local 
  // ⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩⇩
  n = GetNumStacks();
  
  if (me != 0) {
      return 0;
  }

  h.clear();
  h.resize(n);
  // hset.clear();
  _forn(i, 0, n) {
    h [i] = GetStackHeight(i + 1);
    // hset.insert(mp(h [i], i));
    htotal += h [i];
  }
  hupl.clear();
  hupl.resize(n);
  // int diffI = -1;
  _forn(i, 0, n) {
    hupl [i] = getUpl(i);
    // fprintf(stderr, "> hupl [%d] = %lld\n", i, hupl [i]);
    // if (i > 0 && hupl [i] < hupl [i - 1] && diffI < 0) diffI = i;
  }

  MODULO = 1000000007;
  rtv = 0;
  int i = 0, rlb = 0;
  while (i < n) {
    // hset.erase(mp(h [i], i));
    if (i == rlb) ++ rlb;
    while (rlb < n && 0 == h [rlb]) ++ rlb;

    if (h [i] == hupl [i]) {
      ++ i;
      continue;
    }

    if (h [i] > hupl [i]) {
      incRtv(h [i] - hupl [i]);
      // modify
      // hset.erase(mp(h [i + 1], i + 1));
      h [i + 1] += h [i] - hupl [i];
      h [i] = hupl [i];
      // hset.insert(mp(h [i + 1], i + 1));
      ++ i;
      continue;
    }

    // std::set< pair<tll, int> >::iterator it;
    // it = hset.lower_bound (mp(i + 1, hupl [n - 1] + 1));   
    
    // it = hset.end();
    // -- it;

    // if (it == hset.end()) {
      // it = hset.lower_bound (mp(diffI, hupl [diffI] + 1));    
    // }

    // assert(it != hset.end());

    // tll dh = min(it->first, hupl [i] - h [i]);
    tll dh = min(h [rlb], hupl [i] - h [i]);
    h [i] += dh;

    // int pe = it->second;
    int pe = rlb;
    incRtv((dh % MODULO) * (pe - i));
    h [pe] -= dh;
    // hset.erase(it);
    // hset.insert(mp(h [pe], pe));

    if (hupl [i] != h [i]) {
      // hset.insert(mp(h [i], i));
    } else {
      ++ i;
    }
  }

  printf("%lld\n", rtv);
  // fprintf(stderr, "> current node = %d, from = %d, to = %d\n", me, from, to);

  return 0;
}
