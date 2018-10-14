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
        = IDE_PATH + "GoogleCodeJam/2018/Round_2/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "GoogleCodeJam/2018/Round_2/output.txt";

int init() {
    // ...
}

// MY
int R, B;
vector< pair<int, int> > p;
int f [2][510][510];

int solve() {
    p.clear ();
    p.reserve((R + 1) * (B + 1));
    int m = max(R, B);
    p.push_back(make_pair(0, 0));
    for (int i = 1; i <= m; ++ i) {
        for (int c = 0; c < i; ++ c) {
            p.push_back (make_pair(i, c));
            p.push_back (make_pair(c, i));
        }
        p.push_back(make_pair(i, i));
    }
    int n = p.size();
    memset(f, 0, sizeof(f));
    f [0][R][B] = 1;
    int nlev = 0, lev = 0;
    for (int i = 0; i + 1 < n; ++ i) {
        lev = i & 1, nlev = (i+1) & 1;
        int mr = p [i + 1].first;
        int mb = p [i + 1].second;
        for (int r = 0; r <= R; ++ r) {
            for (int b = 0; b <= B; ++b) {
                if (f[lev][r][b] > 0) {
                    f[nlev][r][b] = max(f[nlev][r][b], f[lev][r][b]);
                    if (r-mr>=0 && b-mb>=0) {
                        f[nlev][r - mr][b - mb] = max (f[nlev][r - mr][b - mb], f[lev][r][b] + 1);
                    }
                }
            }
        }
    }
    return f[nlev][0][0]-1;
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    init();

    // CODE AREA =>
    // forT(testId) {
    for (R = 1; R <= 20; ++ R)
        for (B = 1; B <= 20; ++ B) {
        // scanf("%d %d", &R, &B);
            int testId = -1;
        // printf ("Case #%d: %d\n", testId + 1, solve());
            printf ("Case #%d %d: %d\n", R, B, solve());
    }

    // CODE AREA <= 

    return 0;
}