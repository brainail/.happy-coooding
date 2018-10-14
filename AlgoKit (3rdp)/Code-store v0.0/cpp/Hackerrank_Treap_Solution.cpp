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

#include <inttypes.h>
#include <ctype.h>
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
const bool DEBUG = false;
const int MAXN = 100000 + 10;
int N, Q, X, Y, L, R, qt;

typedef struct item * pitem;

struct item {
    int prior, value, cnt;
    bool rev;
    pitem l, r, p;
    item () { }
    item (int value, int prior) : value (value), prior (prior), l(NULL), r(NULL), cnt(1), rev(false) { }
};

pitem elements;
pitem elements_tpos [MAXN];
vector<int> rnd_prior;

int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void upd_prv (pitem it) {
    if (it) {
        if (it->l) it->l->p = it;
        if (it->r) it->r->p = it;
    }
}

void push (pitem it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
    push (l);
    push (r);
    if (!l || !r) t = l ? l : r;
    else if (l->prior > r->prior) merge (l->r, l->r, r), t = l;
    else merge (r->l, l, r->l), t = r;
    upd_cnt (t);
    upd_prv (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t) return void(l = r = 0);
    push (t);
    int cur_key = add + cnt(t->l);
    if (key <= cur_key) split (t->l, l, t->l, key, add), r = t;
    else split (t->r, t->r, r, key, add + 1 + cnt(t->l)), l = t;
    upd_cnt (t);
    upd_prv (t);
}

void reverse (pitem t, int l, int r) {
    pitem t1, t2, t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r - l + 1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}

void insert (pitem & t, int pos, int elem) {
    pitem t1, t2;
    split (t, t1, t2, pos);
    elements_tpos [pos] = new item(elem, rnd_prior [pos]);
    merge (t1, t1, elements_tpos [pos]); 
    merge (t, t1, t2);
} 

void output (pitem t) {
    if (!t) return;
    push (t);
    output (t->l);
    printf ("t->value = %d\n", t->value);
    output (t->r);
}

int get (pitem & t, int index) {
    if (!t) return -1;
    push (t);
    if (index < cnt(t->l))
        return get(t->l, index);
    else if (index > cnt(t->l))
        return get(t->r, index - cnt(t->l) - 1);
    return t->value;
}

int search (pitem ft) {
    vector<pitem> way;
    pitem curt = ft;
    while (curt) {
        way.PB(curt);
        curt = curt->p;
    }
    reverse(ALL(way));

    // DEBUG
    if (DEBUG) {
        printf("--- Debug Information ---\n");
        _FORN(i, 0, SIZE(way)) printf("way:t->value = %d\n", way [i]->value);
    }

    pitem t = elements;
    int add = 0, cur_pos = -1, Nw = SIZE(way);
    _FORN(i, 0, Nw) {
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
    _FORN(i, 0, N) rnd_prior.push_back(i);
    random_shuffle(ALL(rnd_prior));
    _FORN(i, 0, N) insert(elements, i, i);

    // DEBUG
    if (DEBUG) {
        printf("--- Debug Information ---\n");
        output(elements); 
    }
}

int main() {
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);  
    
    scanf("%d %d", &N, &Q);
    init ();  

    _FORN(qId, 0, Q) {
        scanf("%d", &qt);

        if (1 == qt) {
            scanf("%d %d", &L, &R);
            reverse (elements, L - 1, R - 1);
        } else if (2 == qt) {
            scanf("%d", &X);
            printf("element %d is at position %d\n", X, search (elements_tpos [X - 1]) + 1); 
        } else if (3 == qt) {
            scanf("%d", &Y);
            printf("element at position %d is %d\n", Y, get (elements, Y - 1) + 1); 
        }
    }

    return 0;
}