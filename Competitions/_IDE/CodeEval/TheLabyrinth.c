// INCLUDES
// #define __INCLUDE_MANUAL
#ifndef __INCLUDE_MANUAL
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#endif

#define __INCLUDE_STDC
#ifndef __INCLUDE_STDC
#include <bits/stdc++.h>
using namespace std;
#endif

#define __INCLUDE_PBDS
#ifndef __INCLUDE_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#endif

#define __INCLUDE_CTYPES
#ifndef __INCLUDE_CTYPES
#include <inttypes.h>
#include <ctype.h>
#endif

// TYPEDEFS
typedef long long tll;
typedef long double tld;
typedef unsigned long tul;

#ifndef __INCLUDE_PBDS
// A red-black tree table storing ints and their order
// statistics. Note that since the tree uses
// tree_order_statistics_node_update as its update policy, then it
// includes its methods by_order and order_of_key.
// tree_order_statistics_node_update:: this policy updates nodes' metadata for order statistics.
typedef tree<tll, null_type, less<tll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#endif

// DEFINES
#define forn(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define fordn(index, end, start) for (int index = (int) (end); index >= (int) (start); -- index)
#define _forn(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define _fordn(index, end, start) for (int index = (int) (end); index > (int) (start); -- index)
#define sforn(index, start, end, shift) for (int index = (int) (start); index <= (int) (end); index += shift)
#define sfordn(index, end, start, shift) for (int index = (int) (end); index >= (int) (start); index -= shift)
#define _sforn(index, start, end, shift) for (int index = (int) (start); index < (int) (end); index += shift)
#define _sfordn(index, end, start, shift) for (int index = (int) (end); index > (int) (start); index -= shift)
#define forIt(itIndex, container) for (typeof(container.begin()) itIndex = container.begin(); itIndex != container.end(); ++ itIndex)
#define forT(testId) int __T; scanf("%d\n", &__T); _forn(testId, 0, __T)
// #define fill(box, value) memset(box, value, sizeof(box))
#define fill0(box) memset(box, 0, sizeof(box))
#define fillf(box) memset(box, false, sizeof(box))
#define fill_(box) memset(box, -1, sizeof(box))
#define all(box) box.begin(), box.end()
#define rall(box) box.rbegin(), box.rend()
#define csize(box) ((int) (box.size()))
#define clen(box) ((int) (box.length()))
#define mp(firstItem, secondItem) make_pair(firstItem, secondItem)
#define pb(value) push_back(value)
#define pw2(power) (1 << (power))
#define pw2l(power) (((LL) (1)) << (power))
#define hasBit(mask, index) (((mask) & pw2(index)) != 0)
#define hasBitl(mask, index) (((mask) & pw2l(index)) != 0)
#define calcBits(value) (__builtin_popcount(value))
#define allMasks(maskIndex, length) for (int maskIndex = 0; maskIndex < TWOP(length); ++ maskIndex)
#define allSubmasks(maskIndex, mask) for (int maskIndex = mask; ; maskIndex = ((maskIndex - 1) & mask))
#define contain(container, key) (container.find(key) != container.end())
#define debug(who) cout << #who << " = " << who << endl;
#define debug2(who, who2) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl;
#define debug3(who, who2, who3) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl;
#define debugp(who) cout << #who << " = (" << who.first << ", " << who.second << ")" << endl;
#define endl '\n'

// CONSTS
const tld EPS = 1e-9;
const int INF = 1000000000;
const tll INFL = (tll) 1000000000 * (tll) 1000000000;

char INPUT_FILE [100]
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/input.txt";
char OUTPUT_FILE [100]
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/output.txt";

// MY
char s [200];
char board [200][200];
int dist [200][200];
int fromx [200][200], fromy [200][200];
int v [4][2] = {{+1, +0}, {-1, +0}, {+0, +1}, {+0, -1}};
int n, m;
int qx [200 * 200], qy [200 * 200];
int i, j;

inline bool isFree(int x, int y) {
    return ' ' == board [x][y];
}

void calcTest() {
    memset(dist, -1, sizeof(dist));
    memset(fromx, -1, sizeof(fromx));
    memset(fromy, -1, sizeof(fromy));

    int cq = 0, nq = 0;
    for (j = 0; j < m; ++ j)
        if (isFree(0, j)) {
            board [0][j] = 'X', dist [0][j] = 0;
            qx [nq] = 0, qy [nq] = j, ++ nq;
        }

    while (cq < nq) {
        int statex = qx [cq], statey = qy [cq];
        ++ cq;

        for (i = 0; i < 4; ++ i) {
            int nx = statex + v [i][0], ny = statey + v [i][1];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && isFree(nx, ny)) {
                board [nx][ny] = 'X';
                dist [nx][ny] = dist [statex][statey] + 1;
                fromx [nx][ny] = statex, fromy [nx][ny] = statey;
                qx [nq] = nx, qy [nq] = ny;
                ++ nq;
            }
        }
    }

    int rx = -1, ry = -1;
    for (j = 0; j < m; ++ j)
        if ((rx < 0 && dist [n - 1][j] >= 0) || (dist [n - 1][j] >= 0 && dist [n - 1][j] < dist [rx][ry])) {
            rx = n - 1, ry = j;
        }

    while (rx >= 0) {
        board [rx][ry] = '+';
        int fpx = fromx [rx][ry], fpy = fromy [rx][ry];
        rx = fpx, ry = fpy;
    }

    for (i = 0; i < n; ++ i)
        for (j = 0; j < m; ++ j)
              if ('X' == board [i][j]) {
                  board [i][j] = ' ';
              }

    for (i = 0; i < n; ++ i) {
        for (j = 0; j < m; ++ j) {
            printf("%c", board [i][j]);
        }
        printf("\n");
    }
}

// MAIN
int main(int argc, char * argv []) {
    freopen(argv [1], "r", stdin);
    // freopen(INPUT_FILE, "r", stdin);
    // freopen(OUTPUT_FILE, "w", stdout);

    // sleep(10);

    // CODE AREA =>
    n = 0, m = -1;

    memset(board, ' ', sizeof(board));
    char buf [200];
    while (fgets (buf, sizeof(buf), stdin)) {
        int len = 0;
        for (j = 0; j < strlen (buf); ++ j) {
            if (' ' == buf [j] || '*' == buf [j]) {
                board [n][len ++] = buf [j];
            }
        }

        if (m < 0) m = len;
        ++ n;
        if (n == m) break;
    }

    calcTest();
    // CODE AREA <=

    return 0;
}