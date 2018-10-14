// INCLUDES
#include <cassert>
#include <cmath>

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>

#include <cstring>
#include <string>

#include <vector>

using namespace std;

// TYPEDEFS
typedef long long TLL;
typedef vector < int > VI;

// DEFINES
#define FORN(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define FORDN(index, end, start) for (int index = (int) (end); index >= (int) (start); -- index)
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define _FORDN(index, end, start) for (int index = (int) (end); index > (int) (start); -- index)
#define FILL(box, value) memset(box, value, sizeof(box))
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define PB(value) push_back(value)

// CONSTS
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline bool IS_DIGITCH(char C) { return C >= '0' && C <= '9'; }

// MY
const int MAXC = 2000 + 10;
const int MAXJ = 12000 + 10;

int circuit_H[MAXC], circuit_E[MAXC], circuit_P[MAXC];
VI jcircuit[MAXJ];
int jcp[MAXJ][MAXC];
int juggle_H[MAXJ], juggle_E[MAXJ], juggle_P[MAXJ];
VI cjuggle[MAXJ];
int cwhojuggle[MAXJ];
int cjp[MAXC][MAXJ];
int match[MAXJ][MAXC];
int NC, NJ, NL;

inline int calcAssignment(int who) {
    int result = 0;

    _FORN(j, 0, SIZE(jcircuit[who])) {
        result += jcircuit[who][j];
    }

    return result;
}

void goJuggle() {
    string sline;
    int who, H, E, P;

    while (getline(cin, sline)) {
        if (0 == LENGTH(sline) || ('C' != sline[0] && 'J' != sline[0])) continue;
        if ('C' == sline[0]) {
            sscanf(sline.c_str(), "%*c %*c%d %*c:%d %*c:%d %*c:%d", &who, &H, &E, &P);
            circuit_H[who] = H, circuit_E[who] = E, circuit_P[who] = P, ++NC;
        } else if ('J' == sline[0]) {
            sline += ',';
            sscanf(sline.c_str(), "%*c %*c%d %*c:%d %*c:%d %*c:%d", &who, &H, &E, &P);
            juggle_H[who] = H, juggle_E[who] = E, juggle_P[who] = P, ++NJ;

            int pfrom = sline.find("C"), cwho = NULO;
            _FORN(i, pfrom, LENGTH(sline))
                if (IS_DIGITCH(sline[i])) {
                    if (NULO == cwho) cwho = 0;
                    cwho = cwho * 10 + (int)(sline[i] - '0');
                } else if (',' == sline[i]) {
                    if (cwho >= 0) {
                        cjuggle[who].PB(cwho);
                        jcp[who][cwho] = SIZE(cjuggle[who]) - 1;
                    }

                    cwho = NULO;
                }
        }
    }

    NL = NJ / NC;

    _FORN(i, 0, NJ)
        _FORN(j, 0, NC) {
            match[i][j] = juggle_H[i] * circuit_H[j] + juggle_E[i] * circuit_E[j] + juggle_P[i] * circuit_P[j];
        }

    _FORN(i, 0, NJ)
        _FORN(j, 0, SIZE(cjuggle[i])) {
            int cwho = cjuggle[i][j];
            if (SIZE(jcircuit[cwho]) < NL) {
                jcircuit[cwho].PB(i);
                cjp[cwho][i] = SIZE(jcircuit[cwho]) - 1;
                cwhojuggle[i] = j;
                break;
            }
        }

    bool ok = false;
    while (!ok) {
        ok = true;
        _FORN(i, 0, NJ) {
            bool Jok = false;
            _FORN(j, 0, cwhojuggle[i]) {
                int cwhobest = cjuggle[i][j];
                int cwhonow = cjuggle[i][cwhojuggle[i]];
                _FORN(q, 0, SIZE(jcircuit[cwhobest])) {
                    int jwho = jcircuit[cwhobest][q];
                    if (match[i][cwhobest] > match[jwho][cwhobest]) {
                        ok = false;
                        cwhojuggle[jwho] = jcp[jwho][cwhonow], cwhojuggle[i] = j;

                        swap(jcircuit[cwhobest][cjp[cwhobest][jwho]], jcircuit[cwhonow][cjp[cwhonow][i]]);

                        cjp[cwhobest][i] = cjp[cwhobest][jwho];
                        cjp[cwhobest][jwho] = NULO;

                        cjp[cwhonow][jwho] = cjp[cwhonow][i];
                        cjp[cwhonow][i] = NULO;

                        Jok = true;
                        break;
                    }
                }

                if (Jok) break;
            }
        }
    }

    // printAssignment();
    printf("%d", calcAssignment(1970));
}

void printAssignment() {
    FORDN(i, NC - 1, 0) {
        printf("C%d ", i);
        _FORN(j, 0, SIZE(jcircuit[i])) {
            int jwho = jcircuit[i][j];
            printf("J%d ", jwho);
            _FORN(q, 0, SIZE(cjuggle[jwho])) {
                int cwho = cjuggle[jwho][q];
                printf("C%d:%d", cwho, match[jwho][cwho]);
                if (j + 1 < NL && q + 1 == NC) printf(",");
                if (j + 1 < NL || q + 1 < NC) printf(" ");
            }
        }

        if (i > 0) printf("\n");
    }
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    goJuggle();
    // CODE AREA <=

    return 0;
}