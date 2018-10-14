// INCLUDES
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

// TYPEDEFS
typedef long long TLL;
typedef vector < int > VI;
typedef vector < long long > VLL;

// DEFINES
#define FORN(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define SIZE(box) ((int) (box.size()))
#define PB(value) push_back(value)

// CONSTS
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline TLL TO_LONG(string S) { TLL value; istringstream iss(S); iss >> value; return value; }

// MY
string testCase;

bool calcTest() {
    char END = '*';
    char SPACE = ' ';

    string data;
    testCase += END;
    istringstream sstream(testCase);
    getline(sstream, data, SPACE);
    int a = TO_INTS(data);
    getline(sstream, data, END);
    TLL n = TO_LONG(data);

    if (a <= 1 || n <= 0) return false;

    // Period
    TLL x = (a * a) % 10;
    VI p;
    p.PB(a);
    while (x != a) {
        p.PB(x);
        x = (x * a) % 10;
    }

    // p, p, p, ..., p, ...
    TLL co = n / SIZE(p);
    VLL d (10, 0);
    _FORN (i, 0, SIZE(p)) {
        d [p [i]] += co;
    }

    // ...
    n %= SIZE(p);
    _FORN (i, 0, n) {
        ++ d [p [i]];
    }

    // Print
    _FORN (i, 0, 10) {
        printf("%d: %lld", i, d [i]);
        if (i < 9) printf(", ");
    }

    printf("\n");

    return true;
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