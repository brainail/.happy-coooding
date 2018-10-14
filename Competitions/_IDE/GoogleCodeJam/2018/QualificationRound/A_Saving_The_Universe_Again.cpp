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
        = IDE_PATH + "GoogleCodeJam/2018/QualificationRound/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "GoogleCodeJam/2018/QualificationRound/output.txt";

long long p [63];
long long memo [18000000];
queue<tpii> q;
int n;

int init() {
    for (int i = 0; i < 63; ++ i) p [i] = 1L << i;
}

inline int swapBits(int n, int p1, int p2) {
    int bit1 = 0 != (n & p [p1]), bit2 = 0 != (n & p [p2]);
    return bit1 == bit2 ? n : ((n ^ p [p2]) ^ p [p1]);
}

inline int danger(const int state) {
    int cd = 1, rd = 0;
    for (int i = 0; i < n; ++ i) {
        if (0 != (state & p [i])) cd <<= 1; else rd += cd;
    }
    return rd;
}

inline tpii idx(int x) {
    return make_pair(x / 63, x % 63);
}

int coco;

// MY
int calc(string s, int D) {
    n = s.length();

    int state = 0, swaps = 0;
    for (int i = 0; i < n; ++ i) {
        state += p [i] * (s [i] == 'C' ? 1 : 0);
    }

    if (danger(state) <= D) return 0;

    memset(memo, 0, sizeof(memo));
    q = queue<tpii>();
    q.push(make_pair(state, swaps));

    coco = 0;
    while (!q.empty()) {
        state = q.front().first, swaps = q.front().second;
        q.pop();
        int pstate = state;
        while (pstate > 0) {
            int i = ffs(pstate) - 1;
            if (i + 1 >= n) break;
            pstate ^= p [i];
            int newState = swapBits(state, i, i + 1);
            tpii sidx = idx(newState);
            if (state != newState && !(memo [sidx.first] & p [sidx.second])) {
                if (danger (newState) <= D) return swaps + 1;
                q.push(make_pair(newState, swaps + 1));
                ++ coco;
                memo [sidx.first] |= p [sidx.second];
            }
        }
    }
    
    return -1;
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    init();

    // CODE AREA =>
    forT(testId) {
        int D;
        scanf("%d ", &D);
        string s;
        getline(cin, s);
        int rtv = calc(s, D);
        debug(coco);

        if (rtv < 0) {
            printf ("Case #%d: IMPOSSIBLE\n", testId + 1);
        } else {
            printf ("Case #%d: %d\n", testId + 1, rtv);
        }
    }

    // CODE AREA <= 

    return 0;
}