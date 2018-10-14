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
using namespace std;

// TYPEDEFS
typedef vector < int > VI;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define PB(value) push_back(value)
#define ALL(box) box.begin(), box.end()

// CONSTS
const int NULO = -1;
const int INF = 1000000000;

const string INPUT_FILE
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/input.txt";
const string OUTPUT_FILE
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/CodeEval/output.txt";

// TEMPLATES

// INLINES

// MY
string testCase;
vector<long long> nOp;

bool isPalindrome(long long x);

inline string deletews(string buffData) {
    buffData.erase(std::remove(ALL(buffData), ' '), buffData.end());
    return buffData;
}

void calcTest() {
    long long L, R;
    sscanf(testCase.c_str(), "%lld %lld", &L, &R);

    nOp.assign(R - L + 1, 0);
    long long n0 = 1, n1 = 0;
    long long rtv = 0;

    _FORN(i, 0, R - L + 1) {
        long long X = L + i;
        int isP = (isPalindrome(X) ? 1 : 0);
        nOp [i] = (i > 0 ? nOp [i - 1] : 0) + isP;

        long long np = (nOp [i] % 2) ? n1 : n0;
        if (nOp [i] % 2) ++ n1; else ++ n0;
        rtv += np;
    }

    printf("%lld\n", rtv);
}

bool isPalindrome(long long x) {
    long long y = 0, _x = x;
    while (x > 0) y = y * 10 + (x % 10), x /= 10;
    return (! (_x - y));
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