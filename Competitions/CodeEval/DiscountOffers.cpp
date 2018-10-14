// INCLUDES
#include <cmath>

#include <iostream>
#include <stdio.h>

#include <cstring>
#include <string>

#include <vector>

using namespace std;

// TYPEDEFS

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)

// CONSTS
const long double INF = (long double) 1000000000.0 * (long double) 1000000000.0;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES
template<class T> inline T GCD(T A, T B) { return (A < 0) ? GCD(-A, B) : ((B < 0) ? GCD(A, -B) : ((0 == B) ? A : GCD(B, A % B))); }

// INLINES
inline bool IS_UPPERCH(char C) { return C >= 'A' && C <= 'Z'; }
inline bool IS_LOWERCH(char C) { return C >= 'a' && C <= 'z'; }
inline bool IS_LETTERCH(char C) { return IS_UPPERCH(C) || IS_LOWERCH(C); }
inline char TO_LOWERCH(char C) { return (IS_UPPERCH(C)) ? (C + 32) : C; }

// MY
const int MAX_NODES = 100000;
const int MAX_EDGES = 100000;

string testCase;
int edges, nodes;
int last [MAX_NODES], head [MAX_EDGES], previous [MAX_EDGES];
int flow [MAX_EDGES], cap [MAX_EDGES];
int curflow [MAX_NODES], edge [MAX_NODES];
long double cost [MAX_EDGES];
long double prio [MAX_NODES];

inline void clearGraph(int _nodes) {
    fill(last, last + _nodes, -1);
    edges = 0;
    nodes = _nodes;
}

inline void _addEdge(int u, int v, int _cap, long double _cost) {
    head [edges] = v;
    cap [edges] = _cap;
    cost [edges] = _cost;
    flow [edges] = 0;
    previous [edges] = last [u];
    last [u] = edges ++;
}

inline void addEdge(int u, int v, int cap, long double cost) {
    _addEdge(u, v, cap, cost);
    _addEdge(v, u, 0, -cost);
}

pair<int, long double> offerAll(int s, int t) {
    int f = 0;
    long double flowCost = 0;

    while (true) {
        fill(prio, prio + nodes, -INF);
        curflow [s] = INF, prio [s] = 0;

        for (int k = 0, wasChanged = true; k < nodes && wasChanged; ++ k) {
            wasChanged = false;
            for (int u = 0; u < nodes; u++) {
                if (prio [u] <= -INF + 1) continue;
                for (int e = last [u]; e >= 0; e = previous [e]) {
                    int v = head [e];
                    long double nprio = prio [u] + cost [e];
                    if (cap [e] > flow [e] && prio [v] < nprio) {
                        prio [v] = nprio, edge [v] = e, wasChanged = true;
                        curflow [v] = min(curflow [u], cap [e] - flow [e]);
                    }
                }
            }
        }

        if (prio [t] <= -INF + 1) break;

        int df = curflow [t];
        f += df, flowCost += df * prio [t];

        for (int v = t; v != s; v = head [edge [v] ^ 1]) {
            flow [edge [v]] += df, flow [edge [v] ^ 1] -= df;
        }
    }

    return MP(f, flowCost);
}

const string VOWELS = "aeiouy";

inline long double calcCost(string customer, string product) {
    int ssA = 0, ssB = 0;
    _FORN(i, 0, LENGTH(customer)) {
        int isVowel = VOWELS.find(customer [i]) != string::npos;
        ssA += isVowel, ssB += !isVowel;
    }

    long double ssR = (LENGTH(product) % 2) ? ssB : ssA * 1.5;
    if (GCD(LENGTH(customer), LENGTH(product)) > 1) ssR *= 1.5;

    return ssR;
}

void calcTest() {
    testCase += ",";
    vector<string> customers, products;
    customers.reserve(100), products.reserve(100);

    string stuff = "";
    bool productsTime = false;

    _FORN(i, 0, LENGTH(testCase)) {
        if (',' == testCase [i] || ';' == testCase [i]) {
            if (productsTime) products.PB(stuff); else customers.PB(stuff);
            productsTime |= (';' == testCase [i]), stuff = "";
        }

        if (IS_LETTERCH(testCase [i])) {
            stuff += TO_LOWERCH(testCase [i]);
        }
    }

    // Bad input line, skip
    if (!productsTime) return;

    int N = SIZE(customers), M = SIZE(products);
    clearGraph(N + M + 2);

    _FORN(i, 0, N)
        _FORN(j, 0, M) {
            long double cost = calcCost(customers [i], products [j]);
            addEdge(i + 1, N + j + 1, 1, cost);
        }

    _FORN(i, 0, N) addEdge(0, i + 1, 1, 0);
    _FORN(j, 0, M) addEdge(N + j + 1, N + M + 1, 1, 0);

    pair<int, long double> result = offerAll(0, N + M + 1);
    printf("%.2Lf\n", result.second);
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    while (getline(cin, testCase)) calcTest();
    // CODE AREA <=

    return 0;
}