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
        = IDE_PATH + "HackerEarth/2016/AprilCircuits/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "HackerEarth/2016/AprilCircuits/output.txt";

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
const bool DEBUG = true;
const int MAXN = 500000 + 10;
int N, Q;

typedef struct item * pitem;

struct item {
    tll prior;
    int cnt;
    tll value;
    bool rev;
    tll sum;
    tll delta;
    pitem l, r, p;
    item () { }
    item (tll value, tll prior) :
            value (value),
            prior (prior),
            l(NULL),
            r(NULL),
            cnt(1),
            rev(false),
            delta(0),
            sum(value) { }
};

pitem elements;
pitem elements_tpos [MAXN];
vector<tll> rnd_prior;

static tll modifyOp(tll x, tll y) {
    return x + y;
}

static tll queryOp(tll x, tll y) {
    return x + y;
}

static int neutralDelta() {
    return 0;
}

static int neutralValue() {
    return 0;
}

static tll deltaEffectOnSegmentOp(tll delta, tll segmentLength) {
    // Here you must write a fast equivalent of following slow code:
    // int result = delta;
    // for (int i = 1; i < segmentLength; i++) result = queryOp(result, delta);
    // return result;

    // max
    // return delta;

    // sum
    return delta * segmentLength;
}

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

tll sum (pitem it) {
    return it ? it->sum : neutralValue ();
}

void upd_cnt (pitem it) {
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void upd_sum (pitem it) {
    it->sum = queryOp(queryOp(sum(it->l), it->value), sum(it->r));
}

void upd_prv (pitem it) {
    if (it->l) it->l->p = it;
    if (it->r) it->r->p = it;
    it->p = NULL;
}

void upd (pitem it) {
    if (! it) return;
    upd_cnt (it);
    upd_sum (it);
    upd_prv (it);
}

void push_rev (pitem it) {
    if (! it->rev) return;
    it->rev = false;
    swap (it->l, it->r);
    if (it->l) it->l->rev ^= true;
    if (it->r) it->r->rev ^= true;
}

void applyDelta(pitem it, tll delta) {
    if (! it) return;
    it->delta = modifyOp(it->delta, delta);
    it->value = modifyOp(it->value, delta);
    it->sum = modifyOp(it->sum, deltaEffectOnSegmentOp (delta, it->cnt));
}

void push_sum (pitem it) {
    if (! it) return;
    applyDelta(it->l, it->delta);
    applyDelta(it->r, it->delta);
    it->delta = neutralDelta ();
}

void push (pitem it) {
    if (! it) return;
    push_rev (it);
    push_sum (it);
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge (l->r, l->r, r), t = l;
    else merge (r->l, l, r->l), t = r;
    upd (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (! t) return void(l = r = 0);
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key) split (t->l, l, t->l, key, add), r = t; else
    split (t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
    upd (t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r - l + 1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void insert (pitem & t, int who, int pos, tll elem = 0) {
    pitem t1, t2;
    split (t, t1, t2, pos);
    elements_tpos [who] = new item(elem, rnd_prior [who]);
    merge (t1, t1, elements_tpos [who]);
    merge (t, t1, t2);
}

void output (pitem t) {
    if (!t) return;
    push (t);
    output (t->l);
    printf ("t->value = %lld\n", t->value);
    output (t->r);
}

tll get (pitem & t, int index) {
    if (! t) return -1;
    push (t);
    if (index < cnt(t->l)) return get(t->l, index); else
    if (index > cnt(t->l)) return get(t->r, index - cnt(t->l) - 1);
    return t->value;
}

void remove(pitem & t, int index) {
    push(t);
    if (index == cnt(t->l)) merge(t, t->l, t->r); else
    if (index < cnt(t->l)) remove(t->l, index); else
    remove(t->r, index - cnt(t->l) - 1);
    upd (t);
}

// +
void modify(pitem & t, int a, int b, int delta) {
    if (a > b) return;
    pitem l1, r1, l2, r2;
    split(t, l1, r1, b + 1);
    split(l1, l2, r2, a);
    applyDelta(r2, delta);
    pitem tb;
    merge(tb, l2, r2);
    merge(t, tb, r1);
}

// sum
tll query(pitem & t, int a, int b) {
    if (a > b) return neutralValue ();
    pitem l1, r1, l2, r2;
    split(t, l1, r1, b + 1);
    split(l1, l2, r2, a);
    tll rtv = sum(r2);
    pitem tb;
    merge(tb, l2, r2);
    merge(t, tb, r1);
    return rtv;
}

int search (pitem ft) {
    vector<pitem> way;
    pitem curt = ft;
    while (curt) {
        way.pb(curt);
        curt = curt->p;
    }
    reverse(all(way));

    pitem t = elements;
    int add = 0, cur_pos = -1, Nw = csize (way);
    _forn(i, 0, Nw) {
        push (t);
        cur_pos = add + cnt(t->l);

        if (i + 1 < Nw) {
            if (t->r == way [i + 1]) add += 1 + cnt(t->l);
            t = way [i + 1];
        }
    }

    return cur_pos;
}

void init () {
    rnd_prior.assign (N, 0);
    _forn(i, 0, N) rnd_prior [i] = i;
    random_shuffle(all(rnd_prior));
    _forn(i, 0, N) insert(elements, i, i);
}

inline int getHisOrHerPlace(tll hisOrHerValue) {
    int l = 0, r = N - 1;
    while (r - l > 1) {
        int md = (l + r) / 2;
        if (get(elements, md) > hisOrHerValue) l = md; else r = md;
    }

    if (get(elements, r) > hisOrHerValue) return (r + 1) + 1;
    if (get(elements, l) > hisOrHerValue) return (l + 1) + 1;
    return (l) + 1;
}

inline int getHisOrHerInsertIndex(tll hisOrHerValue) {
    int l = 0, r = N - 1;
    while (r - l > 1) {
        int md = (l + r) / 2;
        if (get(elements, md) >= hisOrHerValue) l = md; else r = md;
    }

    if (get(elements, r) >= hisOrHerValue) return r + 1;
    if (get(elements, l) >= hisOrHerValue) return l + 1;
    return l;
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    scanf("%d %d", &N, &Q);
    init ();

    tll rtv = 0;
    _forn(q, 0, Q) {
        int who;
        tll how;
        scanf("%d %lld", &who, &how);
        -- who;

        int whoIndex = search (elements_tpos [who]);
        tll curHow = get(elements, whoIndex);
        int whoPlace = getHisOrHerPlace(curHow);
        rtv -= curHow * whoPlace;

        int oldHowIndex = getHisOrHerInsertIndex(curHow) - 1;
        remove (elements, whoIndex);

        tll newHow = curHow + how;
        int newHowIndex = getHisOrHerInsertIndex(newHow);

        insert (elements, who, newHowIndex, newHow);

        int whoNewPlace = getHisOrHerPlace(newHow);
        rtv += whoNewPlace * newHow;

        int deltaStartIndex = newHowIndex + 1;
        int deltaEndIndex = max (whoIndex, oldHowIndex);
        tll delta = query(elements, deltaStartIndex, deltaEndIndex);
        rtv += delta;

        // printf("%lld", rtv);
        // if (q + 1 < Q) printf("\n");
    }

    // CODE AREA <=

    return 0;
}