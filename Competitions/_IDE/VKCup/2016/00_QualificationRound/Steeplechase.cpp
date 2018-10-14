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
#define endl '\n'

// CONSTS
const tld PI = acos(-1.0);
const tld EPS = 1e-9;
const int INF = 1000000000;
const tll INFL = (tll) 1000000000 * (tll) 1000000000;

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "VKCup/2016/00_QualificationRound/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "VKCup/2016/00_QualificationRound/output.txt";

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
int N, finishPos, offRunLen, jumpLen;
set< pair<int, int> > obstaclesSet;
set< pair<int, int> >::iterator it;
vector<int> obstacles;
vector< pair<int, int> > oo;
vector<int> qq;
vector<int> pp;
vector< pair<int, int> > mo;
vector< pair<int, int> > moRtv;

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    scanf("%d %d %d %d", & N, & finishPos, & offRunLen, & jumpLen);

    obstacles.clear();
    obstacles.reserve((unsigned long) (N + 1));
    obstacles.pb(-1);

    _forn(i, 0, N) {
        int obstaclePos;
        scanf("%d", &obstaclePos);
        obstacles.pb(obstaclePos);
    }

    sort(all(obstacles));
    _forn(i, 1, N + 1) {
        obstaclesSet.insert(mp(obstacles [i], i));
    }

    qq.resize((unsigned long) (N + 10));
    pp.resize((unsigned long) (N + 10));
    mo.resize((unsigned long) (N + 10));

    qq [0] = 0;
    int cq = 0, nq = 1;

    while (cq < nq) {
        int obstacleId = qq [cq];
        ++ cq;

        int curPos = obstacles [obstacleId] + 1;

        // Yay!
        if (obstacleId == N) {
            // restore path ...
            int ccq = cq - 1;
            moRtv.clear();
            moRtv.reserve((unsigned long) (N + 10));
            moRtv.pb(mp(finishPos - curPos, 0));

            while (ccq > 0) {
                moRtv.pb(mo [ccq]);
                ccq = pp [ccq];
            }

            int psz = csize(moRtv);
            for (int i = psz - 1; i >= 0; -- i) {
                if (moRtv [i].first > 0) {
                    printf("RUN %d\n", moRtv [i].first);
                }
                if (moRtv [i].second > 0) {
                    printf("JUMP %d\n", moRtv [i].second);
                }
            }

            return 0;
        }

        // no space
        if (obstacles [obstacleId + 1] - curPos - 1 < offRunLen) {
            continue;
        }

        // run from curPos to ...
        int prevPos = curPos;
        curPos = obstacles [obstacleId + 1] - 1;

        int moooRun = (curPos - prevPos);

        // jump interval
        int jumpStartPos = curPos + 1;
        int jumpEndPos = curPos + jumpLen;

        // try to stay right after obstacle
        oo.clear();
        for (it = obstaclesSet.begin(); it != obstaclesSet.end(); ++ it) {
            if (it->first + 1 > jumpEndPos) break;
            if (it->first + 1 < jumpStartPos) continue;

            oo.pb(* it);

            qq [nq] = (it->second);
            pp [nq] = cq - 1;
            mo [nq] = mp(moooRun, it->first + 1 - curPos);
            ++ nq;
        }

        // remove used obstacles
        for (int i = 0, sz = csize(oo); i < sz; ++ i) {
            obstaclesSet.erase(oo [i]);
        }
    }

    printf("IMPOSSIBLE");
    // CODE AREA <=

    return 0;
}