// INCLUDES
// #define __INCLUDE_MANUAL
#ifndef __INCLUDE_MANUAL
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;
#endif

// TYPEDEFS
typedef pair < int, int > tpii;

#define _forn(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define forT(testId) int __T; scanf("%d\n", &__T); _forn(testId, 0, __T)
#define debug(who) cout << #who << " = " << who << endl;
#define debug2(who, who2) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl;
#define debug3(who, who2, who3) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl;
#define debugp(who) cout << #who << " = (" << who.first << ", " << who.second << ")" << endl;
// #define endl '\n'

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "GoogleCodeJam/2018/Q_Round_A/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "GoogleCodeJam/2018/Q_Round_A/output.txt";

int init() {
    // ...
}

// MY
long long r, b, c;
long long m [1000 + 10], s [1000 + 10], p [1000 + 10];
vector<long long> tt;

long long tota(long long mid) {
    long long total = 0;
    for (int i = 0; i < c; ++ i) {
        if (p [i] > mid) {
            tt [i] = 0;
            continue;
        }
        long long mimi = mid - p [i];
        mimi /= s [i];
        tt [i] = min(mimi, m [i]);
    }
    sort(tt.rbegin(), tt.rend());
    for (int i = 0; i < r; ++ i) {
        total += tt [i];
    }
    return total;
}

long long rtv_lola = -1;
void lola(long long rb, long long uc, long long ss, int cic) {
    if (0 == rb && uc <= r) {
        if (rtv_lola < 0 || ss < rtv_lola) {
            rtv_lola = ss;
        }
    }
    
    if (rb < 0 || uc >= r || cic >= c) {
        return;
    }
    
    for (int bb = 0; bb <= min(m [cic], rb); ++ bb) {
        long long omg = min(m [cic], (long long) bb);
        long long css = (omg * s [cic] + (omg > 0 ? p [cic] : 0));
        long long mss = ss;
        if (mss < 0 || css > mss) mss = css;
        lola(rb - omg, uc + (omg > 0), mss, cic + 1);
    }
}

// MAIN
int main() {
    srand (time(NULL));
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    init();

    // CODE AREA =>
    forT(testId) {
        scanf("%lld %lld %lld", &r, &b, &c);
        long long lo = 0, hi = 0;
        tt.clear ();
        r = 4, b = 20, c = 5;
        for (int i = 0; i < c; ++ i) {
            tt.push_back (0);
            scanf("%lld %lld %lld", &m [i], &s [i], &p [i]);
            m [i] = 1 + (rand() % 15), s [i] = 1 + (rand() % 100), p [i] = 1 + (rand() % 100);
            hi = max(hi, m [i] * s [i] + p [i]);
        }
        
        while (hi - lo > 1) {
            long long mid = (lo + hi) / 2;
            if (tota(mid) >= b) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        
        rtv_lola = -1;
        lola (b, 0, -1, 0);
        
        if (tota(lo) >= b) {
            // printf ("Case #%d: %lld\n", testId + 1, lo);
            // printf ("Case #%d: %lld omg = %lld\n", testId + 1, lo, rtv_lola);
            if (lo != rtv_lola) {
                printf("%lld %lld %lld\n", r, b, c);
                for (int i = 0; i < c; ++ i) {
                    printf ("%lld %lld %lld\n", m[i], s[i], p[i]);
                }
                throw "Why?";
            }
        } else if (tota(hi) >= b) {
            // printf ("Case #%d: %lld\n", testId + 1, hi);
            // printf ("Case #%d: %lld omg = %lld\n", testId + 1, hi, rtv_lola);
            if (hi != rtv_lola) {
                printf("%lld %lld %lld\n", r, b, c);
                for (int i = 0; i < c; ++ i) {
                    printf ("%lld %lld %lld\n", m[i], s[i], p[i]);
                }
                throw "Why?";
            }
        } else {
            // printf ("Case #%d: %lld omg = %lld\n", testId + 1, -1ll, rtv_lola);
            // throw "Why?";
        }
        
        if ((testId % 100000) == 0) {
            printf ("Case #%d: %lld omg = %lld\n", testId + 1, -1ll, rtv_lola);
        }
    }

    // CODE AREA <= 

    return 0;
}