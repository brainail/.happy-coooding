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

// MY
string testCase;

inline string deletews(string buffData) {
    buffData.erase(std::remove(ALL(buffData), ' '), buffData.end());
    return buffData;
}

int dp [1000][1000];

void calcTest() {
    string dataA, dataB;
    istringstream sinput(testCase);

    // length
    getline(sinput, dataA, ',');
    getline(sinput, dataB);

    memset(dp, 0, sizeof(dp));

    int nA = LENGTH(dataA), nB = LENGTH(dataB);

     _FORN(iA, 0, nA)
        dp [iA + 1][1] = (dataA [iA] == dataB [0]) ? 1 : 0;

    _FORN(vB, 2, nB + 1) 
        _FORN(vA, vB, nA + 1) 
            if (dataA [vA - 1] == dataB [vB - 1])
                _FORN(vL, 1, vA)
                    if (dataA [vL - 1] == dataB [vB - 2])
                        dp [vA][vB] += dp [vL][vB - 1];

    int rtv = 0;
    _FORN(vA, 1, nA + 1) rtv += dp [vA][nB];
    cout << rtv << endl;
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