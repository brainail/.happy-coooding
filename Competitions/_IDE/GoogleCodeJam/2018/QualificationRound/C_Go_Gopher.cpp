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

// MY
bool cells [1000 + 10][1000 + 10];

// MAIN
int main() {
    // CODE AREA =>
    int T; 
    scanf("%d", &T);

    for (int testId = 1; testId <= T; ++ testId) {
        int A; 
        scanf("%d", &A);

        int sizeA = 3, sizeB = 3;
        while (sizeA * sizeB < A) {
            ++ sizeA, ++ sizeB;
        }

        for (int i = 3; i <= A; ++ i) {
            for (int j = 3; j <= A; ++ j) {
                if (i * j >= A && abs(A - i * j) <= abs(A - sizeA * sizeB)) {
                    sizeA = i, sizeB = j;
                }
            }
        }

        // fprintf(stderr, "sizeA = %d, sizeB = %d\n", sizeA, sizeB);
        memset(cells, false, sizeof(cells));

        for (int deploy = 0; deploy <= 1000; ++ deploy) {
            int max = 0, go_i = -1, go_j = -1;
            for (int i = 2; i <= sizeA - 1; ++ i) {
                for (int j = 2; j <= sizeB - 1; ++ j) {
                    int empty = 0;
                    for (int x = 0; x <= 2; ++ x) {
                        for (int y = 0; y <= 2; ++ y) {
                            empty += (!cells [i + x][j + y]);
                        }
                    }
                    
                    if (empty > max) {
                        max = empty, go_i = i + 1, go_j = j + 1;
                    }
                }
            }

            printf("%d %d\n", go_i, go_j);
            fflush(stdout);

            int ans_i, ans_j;
            scanf("%d %d", &ans_i, &ans_j);
            
            if (0 == ans_i && 0 == ans_j) {
                // fprintf(stderr, "deploys = %d\n", deploy);
                break;
            }

            cells [ans_i][ans_j] = true;
        }
    }

    // CODE AREA <=

    return 0;
}