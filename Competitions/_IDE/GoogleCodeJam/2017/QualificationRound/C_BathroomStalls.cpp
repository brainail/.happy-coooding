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

#define __INCLUDE_STDC
#ifndef __INCLUDE_STDC
#include <bits/stdc++.h>
using namespace std;
#endif

#define __INCLUDE_PBDS
#ifndef __INCLUDE_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#endif

#define __INCLUDE_CTYPES
#ifndef __INCLUDE_CTYPES
#include <inttypes.h>
#include <ctype.h>
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

#ifndef __INCLUDE_PBDS
// A red-black tree table storing ints and their order
// statistics. Note that since the tree uses
// tree_order_statistics_node_update as its update policy, then it
// includes its methods by_order and order_of_key.
// tree_order_statistics_node_update:: this policy updates nodes' metadata for order statistics.
typedef tree<tll, null_type, less<tll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#endif

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
        = IDE_PATH + "GoogleCodeJam/2017/QualificationRound/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "GoogleCodeJam/2017/QualificationRound/output.txt";

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
vector<bool> used;
vector<int> Ls, Rs;

// 10^3
pair<tll, tll> solve(int n, int k) {
    used.assign(n + 2, false);
    Ls.assign(n + 2, 0);
    Rs.assign(n + 2, 0);
    used [0] = used [n + 1] = true;
    forn(guy, 1, k) {
        _forn(i, 1, n + 1) {
            Ls [i] = (used [i - 1] || used [i]) ? 0 : Ls [i - 1] + 1;
            Rs [n + 1 - i] = (used [n + 2 - i] || used [n + 1 - i]) ? 0 : Rs [n + 2 - i] + 1;
        }
        int stallIndex = -1;
        tll gMaxMinLRs = -INFL;
        tll gMaxMaxLRs = INFL;
        _forn(i, 1, n + 1) {
            if (used [i]) continue;
            int minLRs = min(Ls [i], Rs [i]), maxLRs = max(Ls [i], Rs [i]);
            if (minLRs > gMaxMinLRs) {
                gMaxMinLRs = minLRs, gMaxMaxLRs = maxLRs, stallIndex = i;
            } else if (minLRs == gMaxMinLRs) {
                if (maxLRs > gMaxMaxLRs) {
                    gMaxMinLRs = minLRs, gMaxMaxLRs = maxLRs, stallIndex = i;
                }
            }
        }
        used [stallIndex] = true;
        fprintf (stderr, "%d,", stallIndex);
        if (k == guy) {
            return mp(gMaxMaxLRs, gMaxMinLRs);
        }
    }
    return mp((tll) -1L, (tll) -1L);
}

bool guysCmp(const pair<int, pair<int, int> > & lArg, const pair<int, pair<int, int> > & rArg) {
    if (lArg.first > rArg.first) return true;
    if (lArg.first < rArg.first) return false;
    if (lArg.second.first <= rArg.second.first) return true;
    return false;
}

set<pair<int, pair<int, int> >, bool(*)(const pair<int, pair<int, int> >&, const pair<int, pair<int, int> >&) > guys(&guysCmp);

inline void addStalls(int ll, int rr) {
    guys.insert(mp(rr - ll, mp(ll, rr)));
}

// 10^6
pair<tll, tll> solve2(int n, int k) {
    used.assign(n + 2, false);
    used [0] = used [n + 1] = true;

    guys.clear();
    guys.insert(mp(n + 1, mp(0, n + 1)));
    _forn(i, 0, k - 1) {
        pair<int, pair<int, int> > where = *guys.begin();
        guys.erase (guys.begin());
        int md = (where.second.first + where.second.second) / 2;
        addStalls(where.second.first, md);
        addStalls(md, where.second.second);
        used [md] = true;
    }

    Ls.assign(n + 2, 0);
    Rs.assign(n + 2, 0);
    _forn(i, 1, n + 1) {
        Ls [i] = (used [i - 1] || used [i]) ? 0 : Ls [i - 1] + 1;
        Rs [n + 1 - i] = (used [n + 2 - i] || used [n + 1 - i]) ? 0 : Rs [n + 2 - i] + 1;
    }

    int stallIndex = -1;
    tll gMaxMinLRs = -INFL;
    tll gMaxMaxLRs = INFL;
    _forn(i, 1, n + 1) {
        if (used [i]) continue;
        int minLRs = min(Ls [i], Rs [i]), maxLRs = max(Ls [i], Rs [i]);
        if (minLRs > gMaxMinLRs) {
            gMaxMinLRs = minLRs, gMaxMaxLRs = maxLRs, stallIndex = i;
        } else if (minLRs == gMaxMinLRs) {
            if (maxLRs > gMaxMaxLRs) {
                gMaxMinLRs = minLRs, gMaxMaxLRs = maxLRs, stallIndex = i;
            }
        }
    }
    return mp(gMaxMaxLRs, gMaxMinLRs);
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    forT(testId) {
        int n, k;
        scanf("%d %d", &n, &k);

        pair<tll, tll> rtv = solve(n, k);
        printf ("Case #%d: %d %d\n", testId + 1, rtv.first, rtv.second);
    }

    // CODE AREA <=

    return 0;
}