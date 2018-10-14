#include <message.h>
#include "rps.h"
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
pair<int, char> calcWinner(int n, vector<char> rsp, vector<int> rspId) {
  while (n > 1) {
    for (int i = 0; i < n; i += 2) {
      char chWinner = rsp [i];
      if (rsp [i] == 'R' && rsp [i + 1] == 'S') chWinner = 'R';
      if (rsp [i] == 'S' && rsp [i + 1] == 'R') chWinner = 'R';
      if (rsp [i] == 'S' && rsp [i + 1] == 'P') chWinner = 'S';
      if (rsp [i] == 'P' && rsp [i + 1] == 'S') chWinner = 'S';
      if (rsp [i] == 'P' && rsp [i + 1] == 'R') chWinner = 'P';
      if (rsp [i] == 'R' && rsp [i + 1] == 'P') chWinner = 'P';
      int p = i >> 1;
      rspId [p] = chWinner == rsp [i] ? rspId [i] : rspId [i + 1];
      rsp [p] = chWinner;
    }
    n >>= 1;
  }
  return mp (rspId [0], rsp [0]);
}

pair<int, char> calcWinner(int from, int to) {
  int n = to - from + 1;
  vector<char> rsp(n);
  vector<int> rspId(n);
  _forn(i, 0, n) {
    rspId [i] = from + i;
    rsp [i] = GetFavoriteMove(rspId [i]);
  }
  return calcWinner(n, rsp, rspId);
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
  int _n = GetN();
  int n = 1 << _n;

  if (n < (1 << 28) / 64) {
    if (me != 0) {
      return 0;
    } else {
      pair<int, char> winner = calcWinner(0, n - 1);
      printf("%d\n", winner.first);
      return 0;
    }
  }

  int _nodes = nodes;
  forn(i, 1, _nodes - 1)
    if (! (n % i)) nodes = i;

  if (me == nodes) {
    // calc final res
    vector<pair<int, char>> rspIdCh;
    rspIdCh.clear();
    _forn(fnode, 0, nodes) {
      Receive(fnode);
      int localWinnerId = GetInt(fnode);
      char localWinnerCh = GetChar(fnode);
      // fprintf(stderr, "> from node = %d, lwId = %d, lwCh = %c\n", fnode, localWinnerId, localWinnerCh);
      rspIdCh.pb(mp(localWinnerId, localWinnerCh));
    }
    sort(all(rspIdCh));
    int n = nodes;
    vector<char> rsp(n);
    vector<int> rspId(n);
    _forn(i, 0, n) rsp [i] = rspIdCh [i].second, rspId [i] = rspIdCh [i].first;
    pair<int, char> winner = calcWinner(n, rsp, rspId);
    printf("%d\n", winner.first);
    return 0;
  }

  if (me > nodes) {
    // skip
    return 0;
  }

  int from = n / nodes * me;
  int to = n / nodes * (me + 1);
  if (me == nodes - 1) {
    to = n;
  }

  pair<int, char> localWinner = calcWinner(from, to - 1);

  // Common
  // ↓↓↓↓↓↓
  PutInt(nodes, localWinner.first);
  PutChar(nodes, localWinner.second);
  Send(nodes);

  // fprintf(stderr, "> current node = %d, from = %d, to = %d\n", me, from, to);

  return 0;
}
