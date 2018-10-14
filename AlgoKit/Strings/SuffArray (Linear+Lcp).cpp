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
const int MAXL = 100000 + 10;

class SuffixArray {
public:
    int n, T[MAXL], SA[MAXL], H[MAXL];
    char word[MAXL];

    bool leq(int a1, int a2, int b1, int b2) {
        return a1 < b1 || (a1 == b1 && a2 <= b2);
    }

    bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
        return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3));
    }

    void radixPass(int* a, int* b, int* r, int n, int K) {
        int* c = new int[K + 1];
        for (int i = 0; i <= K; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[r[a[i]]]++;
        for (int i = 0, sum = 0; i <= K; i++) { int t = c[i]; c[i] = sum; sum += t; }
        for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i];
        delete [] c;
    }

    void suffixArray(int* T, int* SA, int n, int K) {
        int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
        int* R = new int[n02 + 3]; R[n02]= R[n02+1]= R[n02+2]=0;
        int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
        int* R0 = new int[n0];
        int* SA0 = new int[n0];
        for (int i=0, j=0; i < n+(n0-n1); i++) if (i%3 != 0) R[j++] = i;
        radixPass(R , SA12, T+2, n02, K);
        radixPass(SA12, R , T+1, n02, K);
        radixPass(R , SA12, T , n02, K);
        int name = 0, c0 = -1, c1 = -1, c2 = -1;
        for (int i = 0; i < n02; i++) {
            if (T[SA12[i]] != c0 || T[SA12[i]+1] != c1 || T[SA12[i]+2] != c2) {
                name++; c0 = T[SA12[i]]; c1 = T[SA12[i]+1]; c2 = T[SA12[i]+2];
            }
            if (SA12[i] % 3 == 1) { R[SA12[i]/3] = name; } else { R[SA12[i]/3 + n0] = name; }
        }
        if (name < n02) {
            suffixArray(R, SA12, n02, name);
            for (int i = 0; i < n02; i++) R[SA12[i]] = i + 1;
        } else {
            for (int i = 0; i < n02; i++) SA12[R[i] - 1] = i;
        }
        for (int i=0, j=0; i < n02; i++) if (SA12[i] < n0) R0[j++] = 3*SA12[i];
        radixPass(R0, SA0, T, n0, K);
        for (int p=0, t=n0-n1, k=0; k < n; k++) {
            #define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
            int i = GetI();
            int j = SA0[p];
            if (SA12[t] < n0 ?
                leq(T[i], R[SA12[t] + n0], T[j], R[j/3]) :
                leq(T[i],T[i+1],R[SA12[t]-n0+1], T[j],T[j+1],R[j/3+n0])){
                SA[k] = i; t++;
                if (t == n02)
                    for (k++; p < n0; p++, k++) SA[k] = SA0[p];
            } else {
                SA[k] = j; p++;
                if (p == n0)
                    for (k++; t < n02; t++, k++) SA[k] = GetI();
            }
        }
        delete [] R; delete [] SA12; delete [] SA0; delete [] R0;
    }

    void calcHeight(int* T, int* SA, int* H, int n) {
        int * rank = new int[n+3];
        int * h = new int[n+3];
        for (int i = 0; i < n; i++) rank[SA[i]] = i;
        for (int i = 0; i < n; i++) {
            if (!rank[i]) h[i]=0;
            else if (!i || h[i - 1] <= 1) {
                int t1 = i, t2 = SA[rank[i] - 1], cnt = 0, mmax = min(n - t1, n - t2);
                for (int j = 0; j < mmax; j++) {
                    if (T[t1 + j] == T[t2 + j]) cnt++;
                    else break;
                }
                h[i] = cnt;
            } else {
                int t1 = i, t2 = SA[rank[i] - 1], cnt = h[i - 1] - 1, mmax = min(n - t1, n - t2);
                for (int j = h[i - 1] - 1; j < mmax; j++) {
                    if (T[t1+j] == T[t2+j]) cnt++;
                    else break;
                }
                h[i] = cnt;
            }
        }
        for (int i = 0; i < n; i++) H[i] = h[SA[i]];
        delete [] rank; delete [] h;
    }

    const static bool DEBUG = false;

    void init() {
        scanf("%s", word);
        n = (int) strlen(word);
        for (int i = 0; i < n; i++) {
            T[i] = word[i] - 'a' + 1;
        }
        T[n] = T[n + 1] = T[n + 2] = 0;
        suffixArray(T, SA, n, 26);
        calcHeight(T, SA, H, n);

        // DEBUG
        if (DEBUG) {
            printf(" === DEBUG DATA ===\n");
            for (int i = 0; i < n; i++) printf("SA[%d] = %d H[%d] = %d\n", i, SA[i], i, H[i]);
            printf(" === DEBUG DATA ===\n");
            for (int i = 0; i < n; i++) printf("fcalc(%d) = %lld\n", i+1, fcalc(i+1));
        }
    }

    // FDEBUG
    LL fcalc(int slen) {
        int cnt = 1, i = 0;

        while (i < n) {
            int j = i;
            while (j + 1 < n && H[j + 1] >= slen) ++ j;
            cnt = max(cnt, j - i + 1);
            i = j + 1;
        }

        return (LL) cnt * (LL) slen;
    }

    PII Qs [MAXL], Ls [MAXL];

    static inline bool sort_cmp (PII A, PII B) {
        if (A.first > B.first) return true;
        if (A.first < B.first) return false;
        return A.second < B.second;
    }

    LL calc() {
        LL res = n;

        _FORN(i, 1, n) {
            Qs [i] = MP(H [i], i);
            Ls [i] = MP(i - 1, i + 1);
        }

        sort(Qs + 1, Qs + n, sort_cmp);

        // DEBUG
        if (DEBUG) {
            printf(" === DEBUG DATA ===\n");
            for (int i = 1; i < n; i++) printf("Qs[%d].first = %d Qs[%d].second = %d\n", i, Qs [i].first, i, Qs [i].second);
            printf(" === DEBUG DATA ===\n");
        }

        _FORN(i, 1, n) {
            int l = Ls [Qs [i].second].first + 1, r = Ls [Qs [i].second].second - 1;
            res = max(res, (LL) (r - l + 2) * (LL) Qs [i].first);

            // DEBUG
            if (DEBUG) {
                printf("Len = %d, Cnt = %d\n", Qs [i].first, (r - l + 2));
            }

            Ls [Ls [Qs [i].second].first].second = Ls [Qs [i].second].second;
            Ls [Ls [Qs [i].second].second].first = Ls [Qs [i].second].first;
        }

        return res;
    }

};

int lower, upper;
SuffixArray sa;

int main() {
    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);
    sa.init();

    LL res = sa.calc();
    printf("%lld", res);
    return 0;
}