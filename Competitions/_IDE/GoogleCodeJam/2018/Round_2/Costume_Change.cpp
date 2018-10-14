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
#include <set>
#include <map>

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
int n;
vector<int> co;
map< vector<int>, int > memo;
int result = 1000000000;

void solve(int move, vector<int> board) {
    if (memo.count (board) && move >= memo [board]) {
        return;
    } else {
        memo [board] = move;
    }
    
    set<int> env;
    bool good = true;
    int mk = 0, mi, mj;
    set<int> menv;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++j) {
            // vector<int> next_board(board);
            env.clear ();
            int k = 0;
            
            env.insert(board [(i+0)*n+(j+0)]);
            if (i > 0) {
                k += board [(i-1)*n+(j+0)] == board [(i+0)*n+(j+0)];
                env.insert(board [(i-1)*n+(j+0)]);
            }
            if (i+1 < n) {
                k += board [(i+1)*n+(j+0)] == board [(i+0)*n+(j+0)];
                env.insert(board [(i+1)*n+(j+0)]);
            }
            if (j > 0) {
                k += board [(i+0)*n+(j-1)] == board [(i+0)*n+(j+0)];
                env.insert(board [(i+0)*n+(j-1)]);
            }
            if (j+1 < n) {
                k += board [(i+0)*n+(j+1)] == board [(i+0)*n+(j+0)];
                env.insert(board [(i+0)*n+(j+1)]);
            }

            if (k > 0) {
                good = false;
                if (k > mk) {
                    mk = k;
                    mi = i;
                    mj = j;
                    menv = env;
                }
//                for (int t = -n; t <= n; ++ t) {
//                    if (t == 0 || env.count (t)) continue;
//                    next_board [(i+0)*n+(j+0)] = t;
//                    solve(move + 1, next_board);
//                }
            }
        }
    }
    
    if (good) {
        result = min(result, move);
    } else {
        vector<int> next_board(board);
        for (int t = -n; t <= n; ++t) {
            if (t == 0 || menv.count (t)) continue;
            next_board[(mi + 0) * n + (mj + 0)] = t;
            break;
        }
        solve (move + 1, next_board);
    }
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
        scanf("%d", &n);
        co.clear ();
        result = 1000000000;
        for (int i = 0; i < n * n; ++ i) {
            int x;
            scanf("%d", &x);
            co.push_back(x);
        }
        memo.clear();
        solve(0, co);
        printf ("Case #%d: %d\n", testId + 1, result);
    }

    // CODE AREA <= 

    return 0;
}