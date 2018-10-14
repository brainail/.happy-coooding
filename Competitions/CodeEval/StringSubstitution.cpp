// INCLUDES
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

// TYPEDEFS
typedef long long LL;
typedef long double LD;
typedef unsigned long UL;
typedef pair < int, int > PII;
typedef pair < string, string > PSS;
typedef vector < pair < int, int > > VPII;
typedef vector < pair < string, string > > VPSS;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < long long > VLL;
typedef vector < long double > VLD;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define FILL(box, value) memset(box, value, sizeof(box))
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define PB(value) push_back(value)
#define MSG(who) cout << #who << " = " << who << endl;

// CONSTS
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES

// MY
const int MAX_LIMIT = 100000 + 10;

int Ne, tagId;
string testCase;
vector<char> sfind, sreplace;
char expression [MAX_LIMIT], s [MAX_LIMIT], se [MAX_LIMIT];
int used [MAX_LIMIT], z [MAX_LIMIT];

void findAndReplace() {
    // Init
    int Nf = SIZE(sfind);
    int Nr = SIZE(sreplace);
    int Ns = Ne + Nf + 1;

    // Copy
    s [Nf] = '#', z [Nf] = 0, se [Nf] = '$';
    _FORN(i, 0, Nf) s [i] = sfind [i], z [i] = 0, se [i] = '$';
    _FORN(i, 0, Ne) s [Nf + i + 1] = tagId != used [i] ? expression [i] : '@', z [Nf + i + 1] = 0, se [Nf + i + 1] = expression [i];

    // Z-fu, Find
    for (int i = 1, l = 0, r = 0; i < Ns; ++ i) {
        if (i <= r) z [i] = min (r - i + 1, z [i - l]);
        while (i + z [i] < Ns && s [z [i]] == s [i + z [i]]) ++ z [i];
        if (i + z [i] - 1 > r) l = i, r = i + z [i] - 1;
    }

    // Replace
    Ne = 0;
    int findex = Nf + 1;
    while (findex < Ns) {
        if (z [findex] < Nf) {
            used [Ne] = '@' != s [findex] ? NULO : tagId;
            expression [Ne] = se [findex];
            ++ Ne, ++ findex;
            continue;
        }

        findex += Nf;
        _FORN(j, 0, Nr) {
            used [Ne] = tagId;
            expression [Ne] = sreplace [j];
            ++ Ne;
        }
    }
}

void calcTest() {
    testCase += ',', ++ tagId;
    Ne = (int) testCase.find(';');
    if (Ne == string::npos) return;

    _FORN(i, 0, Ne) expression [i] = testCase [i];
    testCase.erase(0, Ne + 1);

    bool found_sfind = false, found_sreplace = false, sinit = false;

    _FORN(i, 0, LENGTH(testCase)) {
        // Skip bad chars
        if ('0' != testCase [i] && '1' != testCase [i] && ',' != testCase [i]) continue;

        // Initialize if needed
        if (!sinit) {
            sinit = true, found_sfind = false, found_sreplace = false;
            sfind.clear(), sfind.reserve(20);
            sreplace.clear(), sreplace.reserve(20);
        }

        // Add to right collection
        if (',' != testCase [i]) {
            if (!found_sfind) sfind.PB(testCase [i]); else sreplace.PB(testCase [i]);
        } else if (!found_sfind) {
            found_sfind = true;
        } else {
            sinit = false, found_sreplace = true;
        }

        // Ok, let's go
        if (found_sfind && found_sreplace) findAndReplace();
    }

    // Print
    _FORN(i, 0, Ne) printf("%c", expression [i]);
    printf("\n");
}

void initAll() {
    FILL(used, NULO);
    tagId = 0;
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    initAll();
    while (getline(cin, testCase)) calcTest();
    // CODE AREA <=

    return 0;
}