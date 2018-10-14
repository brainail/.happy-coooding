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
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }

// MY
string testCase;

inline string deletews(string buffData) {
    buffData.erase(std::remove(ALL(buffData), ' '), buffData.end());
    return buffData;
}

void calcTest() {
    string data;
    istringstream sinput(testCase);

    // length
    getline(sinput, data, '|');
    deletews(data);
    if (data.empty()) return;
    int wlen = TO_INTS(data);

    // last char
    getline(sinput, data, '|');
    deletews(data);
    if (data.empty()) return;
    char lastCh;
    _FORN (i, 0, LENGTH(data))
        if (' ' != data [i]) {
            lastCh = data [i];
            break;
        }

    // text
    VI text;
    text.reserve(100);
    int minCh = INF;
    while (getline(sinput, data, ' ')) {
        deletews(data);
        if (data.empty()) continue;
        int valCh = TO_INTS(data);
        text.PB(valCh);
        minCh = min(minCh, valCh);
    }

    // IT'S HACK FOR AUTHORS. IN RIGHT WAY WE SHOULD USE HASH IN LINEAR TIME.
    // I WROTE THIS BEFORE, BUT NOW IT'S JUST FOR FUN.
    minCh -= (int) (' ');
    _FORN (i, 0, SIZE(text)) printf("%c", (char) (text [i] - minCh));
    printf("\n");
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