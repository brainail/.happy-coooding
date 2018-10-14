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
const int MAXN = 1000;
string testCase;
vector< vector<int> > fits;
int used [MAXN];
int seq [MAXN], foundSeq [MAXN];
int dg [MAXN];
bool found = false;
int N;
int memo [MAXN][MAXN];
int memoMarker = 0;

vector<string> & split(const string & s, char delim, vector<string> & elems, int lo) {
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        if (item.length() > lo) {
            elems.push_back(item);
        }
    }

    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems, 0);
    return elems;
}

inline bool checkFitting(string sbase, string snext) {
    _FORN(i, 1, LENGTH(sbase))
        if (sbase [i] != snext [i - 1]) {
            return false;
        }

    return true;
}

void sentense(int current, int k) {
    // Check Memo
    if (memoMarker == memo [current][k]) return;
    memo [current][k] = memoMarker;

    // Check Flag
    if (found) return;

    // Solution
    if (k == N) {
        found = true;
        _FORN(j, 0, N) foundSeq [j] = seq [j];
        return;
    }

    // Brute
    for (int i = 0, fz = SIZE(fits [current]); i < fz; ++ i) {
        int pnext = fits [current][i];
        
        if (memoMarker != used [pnext]) {
            // Mark
            seq [k] = pnext, used [pnext] = memoMarker;

            // Go ahead
            sentense(pnext, k + 1);

            // Unmark
            seq [k] = 0, used [pnext] = 0;

            // Check Flag
            if (found) break;
        }
    }
}

void calcTest() {
    vector<string> pieces = split(testCase, '|');
    N = SIZE(pieces);

    fits.clear();
    fits.resize(N);

    FILL(dg, 0);
    // FILL(seq, 0);
    // FILL(foundSeq, 0);
    // FILL(memo, 0);
    // FILL(used, 0);
    // memoMarker = 0;

    _FORN(i, 0, N)
        _FORN(j, 0, N) 
            if (i != j && checkFitting(pieces [i], pieces [j])) {
                fits [i].PB(j);
                dg [j] += fits [i][j];
            }

    _FORN(i, 0, N) {    
        ++ memoMarker;

        int startPiece = 0;
        _FORN(i, 0, N)
            if (dg [i] < dg [startPiece]) {
                startPiece = i;
            }
        dg [startPiece] = INF;

        found = false;
        used [startPiece] = memoMarker;
        seq [0] = startPiece;
        sentense(startPiece, 1);

        if (found) break;
    }
    
    printf("%s", pieces [foundSeq [0]].c_str());
    _FORN(i, 1, N) printf("%c", *pieces [foundSeq [i]].rbegin());
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