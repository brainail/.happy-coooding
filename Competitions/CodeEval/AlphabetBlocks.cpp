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

// TEMPLATES

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }

// MY
string testCase;

void calcTest() {
    int inIndex = 0;
    int inLength = LENGTH(testCase);

    // N
    int N = 0;
    while (inIndex < inLength && (testCase [inIndex] == ' ' || testCase [inIndex] == '|')) {
        ++ inIndex;
    }
    while (inIndex < inLength && (testCase [inIndex] != ' ' && testCase [inIndex] != '|')) {
        N = N * 10 + (testCase [inIndex] - '0'), ++ inIndex;
    }

    // Word
    string sword = "";
    while (inIndex < inLength && (testCase [inIndex] == ' ' || testCase [inIndex] == '|')) {
        ++ inIndex;
    }
    while (inIndex < inLength && (testCase [inIndex] != ' ' && testCase [inIndex] != '|')) {
        sword += testCase [inIndex], ++ inIndex;
    }
    int wordLength = LENGTH(sword);

    // Blocks
    vector<string> sblocks(N);
    _FORN(i, 0, N) {
        sblocks [i] = "";
        while (inIndex < inLength && (testCase [inIndex] == ' ' || testCase [inIndex] == '|')) {
            ++ inIndex;
        }
        while (inIndex < inLength && (testCase [inIndex] != ' ' && testCase [inIndex] != '|')) {
            sblocks [i] += testCase [inIndex], ++ inIndex;
        }
    }

    vector< vector<bool> > fits(wordLength);
    _FORN(i, 0, wordLength) {
        fits [i].clear();
        fits [i].resize(N, false);
        _FORN(j, 0, N) fits [i][j] = string::npos != sblocks [j].find(sword [i]);
    }

    vector< vector<bool> > dp(N + 1);
    vector<int> pw(wordLength + 1);

    _FORN(i, 0, wordLength + 1) pw [i] = 1 << i;
    int statesN = pw [wordLength];

    dp [0].clear();
    dp [0].resize(statesN, false);
    dp [0][0] = true;

    _FORN(i, 0, N) {
        dp [i + 1].clear();
        dp [i + 1].resize(statesN, false);

        _FORN(mask, 0, statesN)
            if (dp [i][mask]) {
                dp [i + 1][mask] = true;
                _FORN(j, 0, wordLength)
                    if (!(mask & pw [j]) && fits [j][i])
                        dp [i + 1][mask | pw [j]] = true;
            }
    }

    printf(dp [N][statesN - 1] ? "True\n" : "False\n");
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