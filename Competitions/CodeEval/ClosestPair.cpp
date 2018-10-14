// INCLUDES
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

// TYPEDEFS
typedef vector < int > VI;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define PB(value) push_back(value)
#define ALL(box) box.begin(), box.end()
#define FILL(box, value) memset(box, value, sizeof(box))
#define MSG(who) cout << #who << " = " << who << endl;

// CONSTS
const int NULO = -1;
const int INF = 1000000000;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// MY
struct pt {
    long double x, y;
    int id;
};

const int MAXN = 10000 + 10;
int N;
pt a [MAXN];
double mindist;
int ansa, ansb;
 
inline bool cmp_x (const pt & a, const pt & b) {
    return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}
 
inline bool cmp_y (const pt & a, const pt & b) {
    return a.y < b.y;
}

inline void upd_ans (const pt & a, const pt & b) {
    double dist = sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
    if (dist < mindist) {
        mindist = dist,  ansa = a.id,  ansb = b.id;
    }
}

void find_closest (int l, int r) {
    if (r - l <= 3) {
        _FORN(i, l, r + 1) 
            _FORN(j, i + 1, r + 1) {
                upd_ans (a [i], a [j]);
            }

        sort (a + l, a + r + 1, &cmp_y);
        return;
    }
 
    int m = (l + r) >> 1;
    int midx = a [m].x;
    find_closest (l, m), find_closest (m+1, r);
    static pt t [MAXN];
    merge (a + l, a + m + 1, a + m + 1, a + r + 1, t, &cmp_y);
    copy (t, t + r - l + 1, a + l);
 
    int tsz = 0;
    _FORN(i, l, r + 1) 
        if (abs (a [i].x - midx) < mindist) {
            for (int j = tsz - 1; j >= 0 && a [i].y - t [j].y < mindist; -- j) {
                upd_ans (a [i], t [j]);
            }

            t [tsz ++] = a [i];
        }
}
  
void calcTest() {
    _FORN(i, 0, N) {
        scanf("%Lf %Lf", &a [i].x, &a [i].y);
        a [i].id = i;
    }

    sort (a, a + N, &cmp_x);
    mindist = 1e20;
    find_closest (0, N - 1);

    if (mindist < 10000) {
        printf("%.4lf\n", mindist);
    } else {
        printf("INFINITY\n");
    }
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    scanf("%d", &N);
    while (0 != N) { 
        calcTest();
        scanf("%d", &N);
    }
    // CODE AREA <=

    return 0;
}