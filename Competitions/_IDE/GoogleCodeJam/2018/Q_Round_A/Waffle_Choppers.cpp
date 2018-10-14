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
int n, m, pn, pm, choco, pchoco, vchoco;
char a [100 + 10][100 + 10];
int vcut [100 + 10];
int hcchoco [100 + 10];

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    init();

    // CODE AREA =>
    forT(testId) {
        scanf("%d %d %d %d\n", &n, &m, &pn, &pm);
        choco = 0;
        
        for (int i = 0; i < n; ++ i) {
            string s;
            getline(cin, s);
            for (int j = 0; j < m; ++j) {
                a [i][j] = s [j];
                if ('@' == a [i][j]) ++ choco;
            }
        }
        
        if (0 != (choco % ((pn + 1) * (pm + 1)))) {
            printf ("Case #%d: IMPOSSIBLE\n", testId + 1);
            continue;
        }
        
        pchoco = choco / ((pn + 1) * (pm + 1));
        vchoco = pchoco * (pn + 1);
        
        int vindex = 0;
        int vcchoco = 0;
        vcut [0] = 0;
        for (int v = 0; v < m; ++ v) {
            for (int i = 0; i < n; ++ i) {
                if ('@' == a [i][v]) ++ vcchoco;
            }
            if (vchoco == vcchoco) {
                vcut [++ vindex] = v + 1; // 1 .. m
                vcchoco = 0;
            }
    
            if (vindex == pm) {
                vcut [++ vindex] = m;
                break;
            }
        }
        
        if (vindex != pm + 1) {
            printf ("Case #%d: IMPOSSIBLE\n", testId + 1);
            continue;
        }
        
        int cool = 0;
        memset(hcchoco, 0, sizeof(hcchoco));
        for (int h = 0; h < n; ++ h) {
            for (int t = 0; t < pm + 1; ++ t) {
                for (int j = vcut [t]; j < vcut [t + 1]; ++ j) {
                    if ('@' == a[h][j]) ++ hcchoco [t];
                }
            }
            bool all = true;
            for (int j = 0; j <= pm; ++ j) {
                if (hcchoco[j] != pchoco) {
                    all = false;
                    break;
                }
            }
            
            if (all) {
                ++ cool;
                memset(hcchoco, 0, sizeof(hcchoco));
            }
    
            if (cool == pn) {
                ++ cool;
                break;
            }
        }
        
        if (cool != pn + 1) {
            printf ("Case #%d: IMPOSSIBLE\n", testId + 1);
            continue;
        }
        printf ("Case #%d: POSSIBLE\n", testId + 1);
    }

    // CODE AREA <= 

    return 0;
}