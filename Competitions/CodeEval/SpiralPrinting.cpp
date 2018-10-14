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

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define MSG(who) cout << #who << " = " << who << endl;

// CONSTS
const long double PI = acos(-1.0);
const long double EPS = 1e-9;
const int INF = 1000000000;
const long long INFL = (long long) 1000000000 * (long long) 1000000000;
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// MY
int rows, columns;
vector<string> varray;
vector<bool> used;
string arrayData;
int testIndex = 0;

inline int posxy(int & x, int & y) {
    return x * columns + y;
}

inline void walk(int & x, int & y, int & v) {
    // right
    if (0 == v) ++ y;
    if (0 == v && (y >= columns || used [posxy(x, y)])) v = 1, -- y;
    // down
    if (1 == v) ++ x;
    if (1 == v && (x >= rows || used [posxy(x, y)])) v = 2, -- x;
    // left
    if (2 == v) -- y;
    if (2 == v && (y < 0 || used [posxy(x, y)])) v = 3, ++ y;
    // up
    if (3 == v) -- x;
    if (3 == v && (x < 0 || used [posxy(x, y)])) v = 0, ++ x;
}

inline void calc() {
    if (testIndex) printf("\n");
    ++ testIndex;

    varray.clear();
    used.clear();

    arrayData += " ";
    sscanf(arrayData.c_str(), "%d;%d", &rows, &columns);

    int cells = rows * columns;
    varray.reserve(cells + 1);
    used.reserve(cells + 1);

    int ri = 0;
    while (';' != arrayData [ri]) ++ ri;
    ++ ri;
    while (';' != arrayData [ri]) ++ ri;
    ++ ri;

    _FORN(i, 0, cells) {
        string cur_ch = "";

        while (' ' == arrayData [ri]) ++ ri;
        while (' ' != arrayData [ri]) {
            cur_ch += arrayData [ri];
            ++ ri;
        }

        varray.push_back(cur_ch);
        used.push_back(false);
    }

    int x = 0, y = 0, v = 0;
    _FORN(item, 0, cells) {
        used [posxy(x, y)] = true;
        printf("%s", varray [posxy(x, y)].c_str());
        printf(item + 1 == cells ? "" : " ");
        if (item + 1 == cells) break;
        int px = x, py = y;
        while (px == x && py == y) walk(x, y, v);
    }
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    while (getline(cin, arrayData)) calc();
    // CODE AREA <=

    return 0;
}