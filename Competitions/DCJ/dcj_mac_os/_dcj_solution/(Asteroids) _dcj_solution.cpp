#include <message.h>
#include "asteroids.h"
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
#include <string.h>
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
#define MASTER_NODE 0
#define SENDING_DONE -1
#define LARGE_PRIME 1000000007

vector<vector<int>> dp (2);

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
  // int n = GetHeight();
  // int from = n / nodes * me;
  // int to = n / nodes * (me + 1);
  // if (me == nodes - 1) {
  //   to = n;
  // }

  if (me != 0) {
    return 0;
  }

  int width = GetWidth();
  int height = GetHeight();
  
  dp [0].resize(width, 0);
  dp [1].resize(width, -1);
  int lev = 0;
  int nxtLev = lev^1;

  _forn(t, 0, height) {
    _forn(j, 0, width) {
      if (dp [lev][j] >= 0) {
        char chtj = GetPosition(t, j);
        // 0
        if (chtj == '#') {
          dp [lev][j] = -1;
          continue;
        }

        // 1
        dp [lev][j] += (int) (chtj - '0');

        // 2
        char _chtj = j > 0 ? GetPosition(t, j - 1) : '#';
        if (_chtj != '#' && dp [lev][j] + (int) (_chtj - '0') > dp [nxtLev][j - 1]) {
          dp [nxtLev][j - 1] = dp [lev][j] + (int) (_chtj - '0');
        }

        // 3
        char chtj_ = j + 1 < width ? GetPosition(t, j + 1) : '#';
        if (chtj_ != '#' && dp [lev][j] + (int) (chtj_ - '0') > dp [nxtLev][j + 1]) {
          dp [nxtLev][j + 1] = dp [lev][j] + (int) (chtj_ - '0');
        }

        // 4
        if (dp [lev][j] > dp [nxtLev][j]) {
          dp [nxtLev][j] = dp [lev][j];
        }
      }
    }

    dp [lev].assign(width, -1);
    swap(lev, nxtLev);
  }

  // printf("== dp ==\n");
  // _forn(i, 0, height + 1) {
  //   _forn(j, 0, width) printf("%d ", dp [height -i][j]);
  //   printf("\n");
  // }

  int rtv = -1;
  _forn(j, 0, width)
    if (dp [lev][j] > rtv) rtv = dp [lev][j];

  printf("%d\n", rtv);
}
