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
using namespace std;

// TYPEDEFS
typedef long long TLL;
typedef long double TLD;
typedef unsigned long TUL;
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
#define FORTESTS() int nTests; scanf("%d", &nTests); _FORN(testId, 0, nTests)
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
const TLD PI = acos(-1.0);
const TLD EPS = 1e-9;
const int INF = 1000000000;
const TLL INFL = (TLL) 1000000000 * (TLL) 1000000000;
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES
template<class T> inline int CMPF(T X, T Y = 0, T EPS_DIST = EPS) { return (X <= Y + EPS_DIST) ? ((X + EPS_DIST < Y) ? -1 : 0) : +1; }
template<class T> inline T GCD(T A, T B) { return (A < 0) ? GCD(-A, B) : ((B < 0) ? GCD(A, -B) : ((0 == B) ? A : GCD(B, A % B))); }
template<class T> inline T LCM(T A, T B) { return (A < 0) ? LCM(-A, B) : ((B < 0) ? LCM(A, -B) : (A * (B / GCD(A, B)))); }
template<class T> inline string TO_STRING(T X) { ostringstream oss; oss << X; oss.flush(); return oss.str(); }
template<class T> inline void FIX_MIN(T & B, T A) { if (A < B) B = A; }
template<class T> inline void FIX_MAX(T & B, T A) { if (A > B) B = A; }
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
const int MAXN = 5 * 100000 + 10;
const int MAXP = 22;
const int MAXT = 2;
const int SEGMENT_LIMIT = 3;

int a [MAXT][MAXN];
int vL [MAXT][MAXN], vR [MAXT][MAXN];
int f [MAXT][MAXN / 10][MAXP];
int pw [MAXP], loog [MAXN];

pair<int, int> b [MAXN];
int N, Q, L, K;

void prepare_data() {
    scanf("%d %d", &N, &Q);
    _FORN(i, 0, N) {
        int C;
        scanf("%d", &C);
        b [i] = MP(C, i + 1);
    }

    sort(b, b + N);

    _FORN(i, 0, N) {
        // LEFT
        a [0][b [i].second] = INF;
        if (i > 0 && b [i].first == b [i - 1].first) {
            a [0][b [i].second] = abs(b [i].second - b [i - 1].second);
        }
        // RIGHT
        a [1][b [i].second] = INF;
        if (i + 1 < N && b [i].first == b [i + 1].first) {
            a [1][b [i].second] = abs(b [i].second - b [i + 1].second);
        }
    }

    // ... DEBUG
    // MSG("<---")
    // FORN(i, 1, N) MSG(a [0][i])
    // MSG("--->")
    // FORN(i, 1, N) MSG(a [1][i])
}

inline int vv(int a, int b) {
    return a < b ? a : b;
}

void calc_a(int t) {
    if (N <= 1) return;

    int cvL = a [t][1], cvR = a [t][N];

    FORN(i, 1, N) { 
        cvL = vv(cvL, a [t][i]), cvR = vv(cvR, a [t][N - i + 1]);
        vL [t][i] = cvL, vR [t][N - i + 1] = cvR;
        if (0 == (i % L)) cvL = a [t][i + 1];
        if (1 == ((N - i + 1) % L)) cvR = a [t][N - i];
    }

    FORN(i, 1, K) {
        f [t][i][0] = vR [t][(i - 1) * L + 1];
    }

    // ... DEBUG
    // MSG(t);
    // FORN(i, 1, N) MSG(vL [t][i]);
    // FORN(i, 1, N) MSG(vR [t][i]);
    // FORN(i, 1, K) MSG(f [t][i][0]);

    FORN(ll, 1, L) 
        FORN(i, 1, K - pw [ll] + 1) {
            f [t][i][ll] = vv(f [t][i][ll - 1], f [t][i + pw [ll - 1]][ll - 1]);
        }
}

int calc_v(int t, int l, int r) {
    if (r - l <= SEGMENT_LIMIT) {
        int res = a [t][l];
        FORN(i, l, r) res = vv(res, a [t][i]);
        return res;
    }

    int ll = (l / L) + ((l % L) > 0), rr = (r / L) + ((r % L) > 0), cvL = NULO;

    // ... DEBUG
    // MSG(ll);
    // MSG(rr);
    
    if (ll == rr && 1 == (l % L)) return vL [t][r];
    if (ll == rr && 0 == (r % L)) return vR [t][l];

    if (ll == rr) { 
        cvL = a [t][l];
        FORN(j, l + 1, r) cvL = vv(cvL, a [t][j]);
        return cvL;
    }
        
    ++ ll, -- rr, cvL = vv(vL [t][r], vR [t][l]);
    if (ll > rr) return cvL;
        
    int loo = loog [rr - ll + 1];
    cvL = vv(cvL, vv(f [t][ll][loo], f [t][rr - pw[loo] + 1][loo]));    
    return cvL;
}


void pre_calc() {
    pw [0] = 1; 
    FORN(i, 1, MAXP) pw [i] = pw [i - 1] * 2;

    int loo2 = 0;
    loog [0] = 0;
    _FORN(len, 1, MAXN) {
        while (pw [loo2 + 1] <= len) ++ loo2;
        loog [len] = loo2;
    }

    L = loog [N];
    K = (L > 0) ? ((N / L) + ((N % L) > 0)) : 0;

    // ... DEBUG
    // MSG(L);
    // MSG(K);
    // MSG(".. log2 ..");
    // _FORN(i, 0, 100) {
    //     MSG(i);
    //     MSG(loog [i]);
    // }
}

inline bool isOk(int ll, int rr, int x) {
    // MSG(ll);
    // MSG(rr);
    // MSG(x);
    int minAv = calc_v(0, ll + x, rr);
    // MSG(minAv);
    int minBv = calc_v(1, ll, rr - x);
    // MSG(minBv);
    int minv = min(minAv, minBv);
    // MSG(minv);
    return minv <= x;
}

void solve() {
    _FORN(i, 0, Q) {
        int ll, rr;
        scanf("%d %d", &ll, &rr);

        if (ll == rr) {
            printf("-1\n");
            continue;
        } 

        int dlv = 1, drv = rr - ll;
        while (drv - dlv > 1) {
            int mdv = (dlv + drv) / 2;
            if (isOk(ll, rr, mdv)) drv = mdv; else dlv = mdv;
        }

        int res = NULO;
        if (isOk(ll, rr, dlv)) res = dlv; else
        if (isOk(ll, rr, drv)) res = drv;

        printf("%d\n", res);
    }
}

// MAIN
int main() {
    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);
    // freopen(INPUT_FILE.c_str(), "w", stdout);

    // printf("500000 500000\n");
    // printf("1\n1\n");
    // _FORN(i, 0, 500000 - 2) printf("%d\n", rand() % 2000000000);
    // _FORN(i, 0, 500000) printf("1 500000\n");
    // return 0;

    // CODE AREA =>
    prepare_data();
    pre_calc();
    // LEFT    
    calc_a(0);
    // RIGHT
    calc_a(1);

    // ... DEBUG
    // FORN(t, 0, 1) {
    //     MSG(t);
    //     FORN(i, 1, N)
    //         FORN(j, i, N) {
    //             printf("left = %d .. right = %d --> min = %d\n", i, j, calc_v(t, i, j));
    //         }
    //     }

    // MAIN 
    solve();
    // CODE AREA <=

    return 0;
}