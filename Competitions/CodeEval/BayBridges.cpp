// INCLUDES
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

// TYPEDEFS
typedef long double LD;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define ALL(box) box.begin(), box.end()
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)
#define TWOP(power) (1 << (power))

// CONSTS
const int INF = 1000000000;
const LD EPS = 1e-9;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES
template<class T> inline int CMPF(T X, T Y = 0, T EPS_DIST = EPS) { return (X <= Y + EPS_DIST) ? ((X + EPS_DIST < Y) ? -1 : 0) : +1; }

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline LD TO_DOUBLES(string S) { LD value; istringstream iss(S); iss >> value; return value; }

// MY
struct pt {
    LD x, y;
};

struct Bridge {

    int bridgeId;
    pt from, to;

    friend bool operator < (const Bridge & bA, const Bridge & bB) {
        return bA.bridgeId < bB.bridgeId;
    }

};

string testLine;
vector<Bridge> bridges;
vector< vector<bool> > canTogether;
vector<int> bay, resultBay;
int N, resultBayK;

inline int areaSign (pt a, pt b, pt c) {
    return CMPF((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

inline bool intersect_1 (int a, int b, int c, int d) {
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    return max(a,c) <= min(b,d);
}

bool intersect (pt a, pt b, pt c, pt d) {
    return intersect_1 (a.x, b.x, c.x, d.x)
        && intersect_1 (a.y, b.y, c.y, d.y)
        && areaSign(a,b,c) * areaSign(a,b,d) <= 0
        && areaSign(c,d,a) * areaSign(c,d,b) <= 0;
}

void calc(int K, int brK) {
    if (K == N) {
        if (brK > resultBayK) {
            resultBay = vector<int> (bay.begin(), bay.begin() + brK);
            resultBayK = brK;
        }

        return;
    }

    calc(K + 1, brK);

    bool ok = true;
    _FORN(j, 0, brK)
        if (!canTogether [bay [j]][K]) {
            ok = false;
            break;
        }

    if (ok) {
        bay [brK] = K;
        calc(K + 1, brK + 1);
        bay [brK] = -1;
    }
}

void runSolution() {
    bridges.clear(), bridges.reserve(20);
    while (getline(cin, testLine)) {
        Bridge B;
        string data;
        istringstream sinput(testLine);

        getline(sinput, data, ':');
        B.bridgeId = TO_INTS(data);
        getline(sinput, data, '[');
        getline(sinput, data, ',');
        B.from.x = TO_DOUBLES(data);
        getline(sinput, data, ']');
        B.from.y = TO_DOUBLES(data);
        getline(sinput, data, '[');
        getline(sinput, data, ',');
        B.to.x = TO_DOUBLES(data);
        getline(sinput, data, ']');
        B.to.y = TO_DOUBLES(data);

        bridges.PB(B);
    }

    sort(ALL(bridges));
    N = SIZE(bridges);
    bay.clear(), resultBay.clear(), resultBayK = 0, bay.resize(N, -1);

    canTogether.clear(), canTogether.resize(N, vector<bool> (N, false));
    _FORN(i, 0, N)
        _FORN(j, i + 1, N) {
            canTogether [i][j] = canTogether [j][i] = !intersect(bridges [i].from, bridges [i].to, bridges [j].from, bridges [j].to);
        }


    calc(0, 0);

    _FORN(i, 0, SIZE(resultBay)) printf("%d\n", bridges [resultBay [i]].bridgeId);
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    runSolution();
    // CODE AREA <=

    return 0;
}