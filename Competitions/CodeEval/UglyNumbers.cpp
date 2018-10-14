// INCLUDES
#include <iostream>
#include <stdio.h>

#include <cstring>
#include <string>

using namespace std;

// TYPEDEFS
typedef long long LL;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define FILL(box, value) memset(box, value, sizeof(box))
#define LENGTH(box) ((int) (box.length()))

// CONSTS
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline bool IS_DIGITCH(char C) { return C >= '0' && C <= '9'; }

// MY
const int MAX_LENGTH = 14;
string testCase, expression;
int dp [2][3][5][7][MAX_LENGTH];
LL pn [MAX_LENGTH][MAX_LENGTH];

#define FORREMAINDERS() _FORN(r2, 0, 2) _FORN(r3, 0, 3) _FORN(r5, 0, 5) _FORN(r7, 0, 7)
#define R(c, X, r) (int) (c + (X % r) + r) % r

void calcExpression() {
    int N = LENGTH(expression);

    FILL(dp, 0);
    FILL(pn, 0);
    dp [0][0][0][0][0] = 1;

    _FORN(i, 0, N) {
        LL X = 0;
        _FORN(j, i, N) {
            X = X * 10 + (LL) (expression [j] - '0');
            pn [i][j] = X;
        }
    }

    _FORN(lastPos, 0, N) FORREMAINDERS()
        if (dp [r2][r3][r5][r7][lastPos])
            _FORN(curPos, lastPos + 1, N + 1) {
                LL X = pn [lastPos][curPos - 1];
                dp [R (r2,X,2)][R (r3,X,3)][R (r5,X,5)][R (r7,X,7)][curPos] += dp [r2][r3][r5][r7][lastPos];
                if (lastPos) dp [R (r2,-X,2)][R (r3,-X,3)][R (r5,-X,5)][R (r7,-X,7)][curPos] += dp [r2][r3][r5][r7][lastPos];
            }

    int result = 0;
    FORREMAINDERS() result += dp [r2][r3][r5][r7][N] * (!r2 || !r3 || !r5 || !r7);

    printf("%d\n", result);
}

void calcTest() {
    expression = "";

    _FORN(i, 0, LENGTH(testCase))
        if (IS_DIGITCH(testCase [i])) expression += testCase [i];

    calcExpression();
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