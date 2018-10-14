// INCLUDES
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

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "HackerRank/2016/WeekOfCode24/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "HackerRank/2016/WeekOfCode24/output.txt";

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
int n;
tll k;

vector<int> vunion(vector<int> v1, vector<int> v2) {
    vector<int> v3;
    vector<int> rtv;
    v3.insert(v3.end(), v1.begin(), v1.end());
    v3.insert(v3.end(), v2.begin(), v2.end());
    sort(v3.begin(), v3.end());
    int i = 0;
    while (i < csize(v3)) {
        int j = i;
        while (j < csize(v3) && v3 [j] == v3 [i]) ++ j;
        if ((j - i) % 2) rtv.pb(v3 [i]);
        i=j;
    }
    return rtv;
}

inline void rtv_ins(set<int> & sxor, int x) {
    if (sxor.count (x)) {
        sxor.erase (x);
    } else {
        sxor.insert (x);
    }
}

int was [100000 + 10];
int c_xor [100000 + 10];

vector<int> calc(tll p) {
    vector<bool> p_extra;
    while (p) {
        bool extra = (bool) (p % 2);
        p_extra.pb(extra);
        p = ((p - (int) extra) / 2);
    }
    std::reverse (all(p_extra));

    fill(was, -1);
    c_xor [0] = 0;
    int nx = 1;
    _forn(s, 0, csize(p_extra)) {
        _forn(i, 0, nx) {
            int x = c_xor [i] + c_xor [i];
            if (x >= n) x -= n;
            was [x] = (s == was [x]) ? -1 : s;
            if (p_extra [s]) {
                ++ x;
                if (x >= n) x -= n;
                was [x] = (s == was [x]) ? -1 : s;
            }
        }
        nx = 0;
        _forn(i, 0, n)
            if (was [i] == s) c_xor [nx ++] = i;
    }

    return vector<int> (c_xor, c_xor + nx);
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>

    scanf("%d %lld", &n, &k);
    vector<int> a(n);
    _forn(i, 0, n) scanf("%d", &a [i]);

    bool DEBUG = false;
    if (DEBUG) {
        int p;
        scanf ("%d", &p);

        vector< vector< int>> vxor;
        vxor.resize (n);
        vector< int > lol_rtv_xor;
        _forn(i, 0, n) vxor[i].pb(i);
        _forn(t, 0, k + 1) {
            printf ("XorRow[%d]: ", t);
            _forn(i, 0, n) {
                printf ("( ");
                _forn(j, 0, csize (vxor[i])) printf ("%d ", vxor[i][j]);
                printf (") ");
            }

            if (p == t) {
                lol_rtv_xor = vxor[0];
            }

            printf ("\n");
            vector< vector< int>> vnxor;
            vnxor.resize (n);
            _forn(xi, 0, n) {
                int xj = (xi + 1) % n;
                vnxor[xi] = vunion (vxor[xi], vxor[xj]);
            }
            vxor = vnxor;
        }

        vector<int> rtv_xor = calc(p);

        sort(all(rtv_xor));

        printf("\n");
        _forn(i, 0, csize(lol_rtv_xor)) printf("%d ", lol_rtv_xor [i]);
        printf("\n");
        _forn(i, 0, csize(rtv_xor)) printf("%d ", rtv_xor [i]);
    }

    vector<int> rtv_xor = calc(k - 1);
    int ng = csize (rtv_xor);

    bool SLOW = false;
    if (SLOW) {
        _forn(s, 0, n) {
            int vxor = 0;
            _forn(i, 0, csize (rtv_xor)) {
                int ind = rtv_xor[i] + s;
                if (ind >= n) ind -= n;
                vxor ^= a[ind];
            }
            printf ("%d ", vxor);
        }
        printf ("\n");
    }

    vector<pair<int, int>> gr_xor;
    gr_xor.reserve (ng);
    int ii = 0;
    while (ii < ng) {
        int jj = ii + 1;
        while (jj < ng && rtv_xor [jj - 1] + 1 == rtv_xor [jj]) ++ jj;
        gr_xor.pb(mp(rtv_xor [ii], rtv_xor [jj - 1]));
        ii = jj;
    }

    int ngr = csize(gr_xor);

    int vxor = 0;
    _forn(i, 0, csize (rtv_xor)) {
        vxor ^= a[rtv_xor [i]];
    }

    _forn(s, 0, n) {
        printf("%d ", vxor);
        _forn(i, 0, ngr) {
            int aind = gr_xor [i].first;
            int bind = gr_xor [i].second;
            vxor ^= a [aind];
            ++ aind;
            if (aind >= n) aind -= n;
            ++ bind;
            if (bind >= n) bind -= n;
            vxor ^= a [bind];
            gr_xor [i].first = aind;
            gr_xor [i].second = bind;
        }
    }
    // CODE AREA <=

    return 0;
}