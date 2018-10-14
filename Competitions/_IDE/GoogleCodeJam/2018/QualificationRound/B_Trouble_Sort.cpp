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

int n;
int a [100000 + 10];

// MY
int calc() {
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i + 2 < n; ++ i) {
            if (a [i] > a [i + 2]) {
                done = false;
                swap(a [i], a [i + 2]);
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d,",a[i]);
    }
    printf("\n");
    for (int i = 0; i + 1 < n; ++ i) {
        if (a [i] > a [i + 1]) {
            return i;
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

    // CODE AREA =>
    forT(testId) {
        scanf("%d ", &n);
        for (int i = 0; i < n; ++ i) scanf("%d", &a [i]);
        int rtv = calc();

        if (rtv < 0) {
            printf ("Case #%d: OK\n", testId + 1);
        } else {
            printf ("Case #%d: %d\n", testId + 1, rtv);
        }
    }

    // CODE AREA <=

    return 0;
}