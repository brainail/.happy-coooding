// INCLUDES
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include <string.h>
using namespace std;

// TYPEDEFS

// DEFINES
#define FORN(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)

// CONSTS
const int MAXL = 400 + 10;
const int NULO = -1;
const int MATCH = +3;
const int MISMATCH = -3;
const int INDEL_START = -8;
const int INDEL_EXTENSION = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES

// MY
string testCase;
int dp [MAXL][MAXL][3];
bool okPos [MAXL][MAXL][3];

bool isDnaCh (char ch) {
    // return ('A' == ch || 'C' == ch || 'T' == ch || 'G' == ch);
    return (ch >= 'A' && ch <= 'Z');
}

int similarity (char aCh, char bCh) {
    return (aCh == bCh ? MATCH : MISMATCH);
}

void calcTest () {
    char SEPARATOR = '|';
    string aDna = "", bDna = "";
    bool aOk = true;
    _FORN (i, 0, testCase.length ()) {
        if (aOk && isDnaCh (testCase [i])) aDna += testCase [i]; else
        if (!aOk && isDnaCh (testCase [i])) bDna += testCase [i]; else
        if (SEPARATOR == testCase [i]) aOk = false;
    }

    if (aDna.empty () || bDna.empty ()) return;
    int aN = aDna.length (), bN = bDna.length ();

    memset (dp, NULO, sizeof (dp));
    memset (okPos, false, sizeof (okPos));

    okPos [0][1][1] = true, dp [0][1][1] = INDEL_START;
    FORN (i, 2, bN) okPos [0][i][1] = true, dp [0][i][1] = dp [0][i - 1][1] + INDEL_EXTENSION;

    okPos [1][0][2] = true, dp [1][0][2] = INDEL_START;
    FORN (i, 2, aN) okPos [i][0][2] = true, dp [i][0][2] = dp [i - 1][0][2] + INDEL_EXTENSION;

    okPos [0][0][0] = true, dp [0][0][0] = 0;

    FORN (i, 1, aN)
        FORN (j, 1, bN)
            FORN (t, 0, 2) {
                // ..?X
                // ..?X
                if (okPos [i - 1][j - 1][t]) {
                    int try_match = dp [i - 1][j - 1][t] + similarity (aDna [i - 1], bDna [j - 1]);
                    if (!okPos [i][j][0]) dp [i][j][0] = try_match;
                    okPos [i][j][0] = true, dp [i][j][0] = max (dp [i][j][0], try_match);
                }

                // ..?-
                // ..?X
                if (okPos [i][j - 1][t]) {
                    int try_insert = dp [i][j - 1][t] + (1 != t ? INDEL_START : INDEL_EXTENSION);
                    if (!okPos [i][j][1]) dp [i][j][1] = try_insert;
                    okPos [i][j][1] = true, dp [i][j][1] = max (dp [i][j][1], try_insert);
                }

                // ..?X
                // ..?-
                if (okPos [i - 1][j][t]) {
                    int try_delete = dp [i - 1][j][t] + (2 != t ? INDEL_START : INDEL_EXTENSION);
                    if (!okPos [i][j][2]) dp [i][j][2] = try_delete;
                    okPos [i][j][2] = true, dp [i][j][2] = max (dp [i][j][2], try_delete);
                }
            }

    printf ("%d\n", max (dp [aN][bN][0], max (dp [aN][bN][1], dp [aN][bN][2])));
}

// MAIN
int main (int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str (), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    while (getline (cin, testCase)) calcTest ();
    // CODE AREA <=

    return 0;
}