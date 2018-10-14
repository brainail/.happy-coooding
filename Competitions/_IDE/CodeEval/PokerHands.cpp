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
#define allMasks(maskIndex, length) for (int maskIndex = 0; maskIndex < pw2(length); ++ maskIndex)
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
template<class T> inline string toS(T X) { ostringstream oss; oss << X; oss.flush(); return oss.str(); }
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

const string INPUT_FILE
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/input.txt";
const string OUTPUT_FILE
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/output.txt";

// MY
const static string CARD_VALUE = "0123456789TJQKA";
const static string CARD_SUIT = "DHSC";

string testCase;

inline pair<int, int> parseHandItem(string handItem) {
    return mp ((int) CARD_VALUE.find (handItem [0]), (int) CARD_SUIT.find (handItem [1]));
}

inline bool vseq(vector<pair<int, int>> & hand, int from, int to) {
    _forn(i, from, to) if (hand [i].first + 1 != hand [i + 1].first) return false;
    return true;
}

inline bool vkind(vector<pair<int, int>> & hand, int from, int to) {
    _forn(i, from, to) if (hand [i].first != hand [i + 1].first) return false;
    return true;
}

inline bool skind(vector<pair<int, int>> & hand, int from, int to) {
    _forn(i, from, to) if (hand [i].second != hand [i + 1].second) return false;
    return true;
}

inline pair<int, vector<int>> processHand(vector<pair<int, int>> & hand) {
    sort(all(hand));

    // 1 - royal flush
    if (10 == hand [0].first && vseq (hand, 0, 4) && skind (hand, 0, 4)) {
        return mp (1, vector<int> ());
    }
    // 2 - straight flush
    if (skind (hand, 0, 4) && vseq (hand, 0, 4)) {
        vector<int> v = {hand [4].first};
        return mp (2, v);
    }
    // 3 - four of a kind
    if (vkind (hand, 0, 3)) {
        vector<int> v = {hand [0].first, hand [4].first};
        return mp (3, v);
    } else if (vkind (hand, 1, 4)) {
        vector<int> v = {hand [4].first, hand [0].first};
        return mp (3, v);
    }
    // 4 - full house
    if (vkind (hand, 0, 2) && vkind (hand, 3, 4)) {
        vector<int> v = {hand [0].first, hand [3].first};
        return mp (4, v);
    } else if (vkind (hand, 0, 1) && vkind (hand, 2, 4)) {
        vector<int> v = {hand [2].first, hand [0].first};
        return mp (4, v);
    }
    // 5 - flush
    if (skind (hand, 0, 4) && ! vseq(hand, 0, 4)) {
        vector<int> v = {hand [4].first, hand [3].first, hand [2].first, hand [1].first, hand [0].first};
        return mp (5, v);
    }
    // 6 - straight
    if (vseq (hand, 0, 4) && ! skind (hand, 0, 4)) {
        vector<int> v = {hand [4].first};
        return mp (6, v);
    }
    // 7 - three of kind
    if (vkind (hand, 0, 2)) {
        vector<int> v = {hand [0].first, hand [4].first, hand [3].first};
        return mp (7, v);
    } else if (vkind (hand, 1, 3)) {
        vector<int> v = {hand [1].first, hand [4].first, hand [0].first};
        return mp (7, v);
    } else if (vkind (hand, 2, 4)) {
        vector<int> v = {hand [2].first, hand [1].first, hand [0].first};
        return mp (7, v);
    }
    // 8 - two pair
    if (vkind (hand, 0, 1) && vkind (hand, 2, 3)) {
        vector<int> v = {hand [2].first, hand [0].first, hand [4].first};
        return mp (8, v);
    } else if (vkind (hand, 0, 1) && vkind (hand, 3, 4)) {
        vector<int> v = {hand [3].first, hand [0].first, hand [2].first};
        return mp (8, v);
    }  else if (vkind (hand, 1, 2) && vkind (hand, 3, 4)) {
        vector<int> v = {hand [3].first, hand [1].first, hand [0].first};
        return mp (8, v);
    }
    // 9 - pair
    if (vkind (hand, 0, 1)) {
        vector<int> v = {hand [0].first, hand [4].first, hand [3].first, hand [2].first};
        return mp (9, v);
    } else if (vkind (hand, 1, 2)) {
        vector<int> v = {hand [1].first, hand [4].first, hand [3].first, hand [0].first};
        return mp (9, v);
    } else if (vkind (hand, 2, 3)) {
        vector<int> v = {hand [2].first, hand [4].first, hand [1].first, hand [0].first};
        return mp (9, v);
    } else if (vkind (hand, 3, 4)) {
        vector<int> v = {hand [3].first, hand [2].first, hand [1].first, hand [0].first};
        return mp (9, v);
    }
    // 10 - high card
    vector<int> v = {hand [4].first, hand [3].first, hand [2].first, hand [1].first, hand [0].first};
    return mp (10, v);
};

string calcTest() {
    string val;
    istringstream sinput(testCase);
    vector<pair<int, int>> hand(5);

    _forn(i, 0, 5) {
        getline(sinput, val, ' ');
        hand [i] = parseHandItem(val);
    }
    pair<int, vector<int>> handRtvA = processHand(hand);

    _forn(i, 0, 5) {
        getline(sinput, val, ' ');
        hand [i] = parseHandItem(val);
    }
    pair<int, vector<int>> handRtvB = processHand(hand);

    if (handRtvA.first < handRtvB.first) {
        return "left";
    } else if (handRtvA.first > handRtvB.first) {
        return "right";
    } else {
        _forn(i, 0, csize(handRtvA.second)) {
            if (handRtvA.second [i] > handRtvB.second [i]) {
                return "left";
            } else if (handRtvA.second [i] < handRtvB.second [i]) {
                return "right";
            }
        }
    }

    return "none";
}

// MAIN
int main(int argc, char * argv []) {
    freopen(argv [1], "r", stdin);
    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    while (getline(cin, testCase)) {
        cout << calcTest() << endl;
    }
    // CODE AREA <=

    return 0;
}