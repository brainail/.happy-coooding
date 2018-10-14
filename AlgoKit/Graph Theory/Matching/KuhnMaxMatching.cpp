// INCLUDES
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

// #include <inttypes.h>
// #include <ctype.h>
using namespace std;

// TYPEDEFS
typedef long long LL;
typedef long double LD;
typedef unsigned long UL;
typedef pair < int, int > PII;
typedef pair < string, string > PSS;
typedef vector < pair < int, int > > VPII;
typedef vector < pair < string, string > > VPSS;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < long long > VLL;
typedef vector < long double > VLD;

// DEFINES
#define FORN(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define FORDN(index, end, start) for (int index = (int) (end); index >= (int) (start); -- index)
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define _FORDN(index, end, start) for (int index = (int) (end); index > (int) (start); -- index)
#define SFORN(index, start, end, shift) for (int index = (int) (start); index <= (int) (end); index += shift)
#define SFORDN(index, end, start, shift) for (int index = (int) (end); index >= (int) (start); index -= shift)
#define _SFORN(index, start, end, shift) for (int index = (int) (start); index < (int) (end); index += shift)
#define _SFORDN(index, end, start, shift) for (int index = (int) (end); index > (int) (start); index -= shift)
#define FORIT(itIndex, container) for (typeof(container.begin()) itIndex = container.begin(); itIndex != container.end(); ++ itIndex)
#define FORTESTS(testId) int T; scanf("%d\n", &__T); _FORN(testId, 0, __T)
#define FILL(box, value) memset(box, value, sizeof(box))
#define ALL(box) box.begin(), box.end()
#define RALL(box) box.rbegin(), box.rend()
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)
#define TWOP(power) (1 << (power))
#define TWOLP(power) (((LL) (1)) << (power))
#define CONTAINB(mask, index) (((mask) & TWOP(index)) != 0)
#define CONTAINLB(mask, index) (((mask) & TWOLP(index)) != 0)
#define ONEBITN(value) (__builtin_popcount(value))
#define ALLBSETS(maskIndex, length) for (int maskIndex = 0; maskIndex < TWOP(length); ++ maskIndex)
#define ALLBSUBSETS(maskIndex, mask) for (int maskIndex = mask; ; maskIndex = ((maskIndex - 1) & mask))
#define CONTAINS(container, key) (container.find(key) != container.end())
#define MSG(who) cout << #who << " = " << who << endl;
#define endl '\n'

// CONSTS
const LD PI = acos(-1.0);
const LD EPS = 1e-9;
const int INF = 1000000000;
const LL INFL = (LL) 1000000000 * (LL) 1000000000;
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES
template<class T> inline int CMPF(T X, T Y = 0, T EPS_DIST = EPS) { return (X <= Y + EPS_DIST) ? ((X + EPS_DIST < Y) ? -1 : 0) : +1; }
template<class T> inline T GCD(T A, T B) { return (A < 0) ? GCD(-A, B) : ((B < 0) ? GCD(A, -B) : ((0 == B) ? A : GCD(B, A % B))); }
template<class T> inline T LCM(T A, T B) { return (A < 0) ? LCM(-A, B) : ((B < 0) ? LCM(A, -B) : (A * (B / GCD(A, B)))); }
template<class T> inline string TO_STRING(T X) { ostringstream oss; oss << X; oss.flush(); return oss.str(); }
template<class T> inline void FIX_MIN(T A, T & B) { if (A < B) B = A; }
template<class T> inline void FIX_MAX(T A, T & B) { if (A > B) B = A; }
template<class T> inline T SQR(T X) { return X * X; }

// INLINES
inline bool IS_UPPERCH(char C) { return C >= 'A' && C <= 'Z'; }
inline bool IS_LOWERCH(char C) { return C >= 'a' && C <= 'z'; }
inline bool IS_LETTERCH(char C) { return IS_UPPERCH(C) || IS_LOWERCH(C); }
inline bool IS_DIGITCH(char C) { return C >= '0' && C <= '9'; }
inline char TO_LOWERCH(char C) { return (IS_UPPERCH(C)) ? (C + 32) : C; }
inline char TO_UPPERCH(char C) { return (IS_LOWERCH(C)) ? (C - 32) : C; }
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline double TO_DOUBLES(string S) { double value; istringstream iss(S); iss >> value; return value; }

// MY
class KuhnMatching {

 public:
  const static int MAX_VA = 50000 + 10;
  const static int MAX_VB = 50000 + 10;
  const static int MAX_E = 100000 + 10;

  int last [MAX_VA], next [MAX_E], to [MAX_E], p2 [MAX_VB], p1 [MAX_VA], VA, VB, E;
  bool used [MAX_VA];

  KuhnMatching() { 
    VA = 0, VB = 0, E = 0; 
  }

  KuhnMatching(const int aVA, const int aVB) {  
    resize(aVA, aVB);
  }

  inline void resize(const int aVA, const int aVB) {  
   assert(aVA - 1 < MAX_VA && aVA >= 0 && aVB < MAX_VB && aVB >= 0);
   VA = aVA, VB = aVB, E = 0;
   _FORN(i, 0, VA) last [i] = NULO;
  }  

  inline void addEdge(const int x, const int y) { 
   assert(E < MAX_E && x >= 0 && x < VA && y >= 0 && y < VB);
   next [E] = last [x]; last [x] = E; to [E ++] = y; 
  } 

  bool kuhn(int v) {
   if (used [v]) return false;
   used [v] = true;

   for(int i = last [v]; i >= 0; i = next [i])
    if (NULO == p2 [to [i]] || kuhn(p2 [to [i]])) {
     p2 [to [i]] = v;
     p1 [v] = to[i];
     return true;
    }     

    return false;
  }

  inline int maxMatching() {
   _FORN(i, 0, VA) p1 [i] = NULO; 
   _FORN(i, 0, VB) p2 [i] = NULO; 

   int maxMatching = 0, pMaxMatching = NULO;
   while (maxMatching != pMaxMatching) {
    pMaxMatching = maxMatching;
    memset(used, false, VA);
    _FORN(i, 0, VA)
      if (!used [i] && NULO != last [i] && NULO == p1 [i] && kuhn(i)) {
        ++ maxMatching;
      }
   }

   return maxMatching;
  }

};

KuhnMatching toolKuhn;

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    toolKuhn.resize(5, 5);
    toolKuhn.addEdge(0, 0);
    toolKuhn.addEdge(1, 1);
    toolKuhn.addEdge(2, 2);
    toolKuhn.addEdge(3, 3);
    toolKuhn.addEdge(4, 4);
    assert(5 == toolKuhn.maxMatching());

    toolKuhn.resize(5, 5);
    toolKuhn.addEdge(0, 0);
    toolKuhn.addEdge(1, 0);
    toolKuhn.addEdge(2, 2);
    toolKuhn.addEdge(3, 2);
    toolKuhn.addEdge(4, 4);
    toolKuhn.addEdge(4, 3);
    toolKuhn.addEdge(3, 4);
    assert(4 == toolKuhn.maxMatching());
    // CODE AREA <=

    return 0;
}