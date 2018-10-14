// INCLUDES
// #define __INCLUDE_MANUAL
#ifndef __INCLUDE_MANUAL
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>
#include <cmath>
#include <ctime>
#include <numeric>
#include <iomanip>
#include <complex>
#include <float.h>
#include <cfloat>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include <bitset>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
using namespace std;
#endif

#define __INCLUDE_STDC
#ifndef __INCLUDE_STDC
#include <bits/stdc++.h>
using namespace std;
#endif

#define __INCLUDE_PBDS
#ifndef __INCLUDE_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#endif

#define __INCLUDE_CTYPES
#ifndef __INCLUDE_CTYPES
#include <inttypes.h>
#include <ctype.h>
#endif

// TYPEDEFS
typedef long long tll;
typedef long double tld;
typedef unsigned long tul;
typedef pair < int, int > tpii;
typedef pair < string, string > tpss;
typedef vector < pair < int, int > > tvpii;
typedef vector < pair < string, string > > tvpss;
typedef vector < int > tvi;
typedef vector < string > tvs;
typedef vector < long long > tvll;
typedef vector < long double > tvld;

#ifndef __INCLUDE_PBDS
// A red-black tree table storing ints and their order
// statistics. Note that since the tree uses
// tree_order_statistics_node_update as its update policy, then it
// includes its methods by_order and order_of_key.
// tree_order_statistics_node_update:: this policy updates nodes' metadata for order statistics.
typedef tree<tll, null_type, less<tll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#endif

// DEFINES
#define forn(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define fordn(index, end, start) for (int index = (int) (end); index >= (int) (start); -- index)
#define _forn(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define _fordn(index, end, start) for (int index = (int) (end); index > (int) (start); -- index)
#define sforn(index, start, end, shift) for (int index = (int) (start); index <= (int) (end); index += shift)
#define sfordn(index, end, start, shift) for (int index = (int) (end); index >= (int) (start); index -= shift)
#define _sforn(index, start, end, shift) for (int index = (int) (start); index < (int) (end); index += shift)
#define _sfordn(index, end, start, shift) for (int index = (int) (end); index > (int) (start); index -= shift)
#define forIt(itIndex, container) for (typeof(container.begin()) itIndex = container.begin(); itIndex != container.end(); ++ itIndex)
#define forT(testId) int __T; scanf("%d\n", &__T); _forn(testId, 0, __T)
#define fill(box, value) memset(box, value, sizeof(box))
#define fill0(box) memset(box, 0, sizeof(box))
#define fillf(box) memset(box, false, sizeof(box))
#define fill_(box) memset(box, -1, sizeof(box))
#define all(box) box.begin(), box.end()
#define rall(box) box.rbegin(), box.rend()
#define csize(box) ((int) (box.size()))
#define clen(box) ((int) (box.length()))
#define mp(firstItem, secondItem) make_pair(firstItem, secondItem)
#define pb(value) push_back(value)
#define pw2(power) (1 << (power))
#define pw2l(power) (((LL) (1)) << (power))
#define hasBit(mask, index) (((mask) & pw2(index)) != 0)
#define hasBitl(mask, index) (((mask) & pw2l(index)) != 0)
#define calcBits(value) (__builtin_popcount(value))
#define allMasks(maskIndex, length) for (int maskIndex = 0; maskIndex < TWOP(length); ++ maskIndex)
#define allSubmasks(maskIndex, mask) for (int maskIndex = mask; ; maskIndex = ((maskIndex - 1) & mask))
#define contain(container, key) (container.find(key) != container.end())
#define debug(who) cout << #who << " = " << who << endl;
#define debug2(who, who2) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl;
#define debug3(who, who2, who3) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl;
#define debugp(who) cout << #who << " = (" << who.first << ", " << who.second << ")" << endl;
// #define endl '\n'

// CONSTS
const tld PI = acos(-1.0);
const tld EPS = 1e-9;
const int INF = 1000000000;
const tll INFL = (tll) 1000000000 * (tll) 1000000000;

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "BSUIR2016/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "BSUIR2016/output.txt";

// TEMPLATES
template<class T> inline int cmpf(T X, T Y = 0, T EPS_DIST = EPS) { return (X <= Y + EPS_DIST) ? ((X + EPS_DIST < Y) ? -1 : 0) : +1; }
template<class T> inline T gcd(T A, T B) { return (A < 0) ? gcd(-A, B) : ((B < 0) ? gcd(A, -B) : ((0 == B) ? A : gcd(B, A % B))); }
template<class T> inline T lcm(T A, T B) { return (A < 0) ? lcm(-A, B) : ((B < 0) ? lcm(A, -B) : (A * (B / gcd(A, B)))); }
template<class T> inline string tos(T X) { ostringstream oss; oss << X; oss.flush(); return oss.str(); }
template<class T> inline void fmin(T & B, T A) { if (A < B) B = A; }
template<class T> inline void fmax(T & B, T A) { if (A > B) B = A; }
template<class T> inline T sqr(T X) { return X * X; }

// INLINES
inline bool isUpper(char C) { return C >= 'A' && C <= 'Z'; }
inline bool isLower(char C) { return C >= 'a' && C <= 'z'; }
inline bool isLetter(char C) { return isUpper(C) || isLower(C); }
inline int toI(char C) { return isUpper(C) ? (int) (C - 'A') : (isLower(C) ? (int) (C - 'a') : -1); }
inline bool isDigit(char C) { return C >= '0' && C <= '9'; }
inline char toLower(char C) { return (char) ((isUpper(C)) ? (C + 32) : C); }
inline char toUpper(char C) { return (char) ((isLower(C)) ? (C - 32) : C); }
inline int toInt(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline double toF(string S) { double value; istringstream iss(S); iss >> value; return value; }
inline string deletews(string buffData) { buffData.erase(std::remove(all(buffData), ' '), buffData.end()); return buffData; }

// MY
const int pbs [14][2] = {
        {0, 0}, {0, 1}, {1, 0},
        {0, 2}, {1, 1}, {2, 0},
        {0, 3}, {1, 2}, {2, 1},
        {3, 0}, {0, 4}, {1, 3},
        {2, 2}, {4, 0}
};

string answer;
set<string> S;
vector<string> _S;
int nS;

inline tpii calcBW(string & guess, string & correct) {
    int rtvB = 0, rtvC = 0;
    _forn(i, 0, 4) {
        // B
        if (guess [i] == correct [i]) ++ rtvB;

        // C
        _forn(j, 0, 4)
            if (i != j && guess [i] == correct [j]) {
                ++ rtvC;
                break;
            }
    }

    return mp(rtvB, rtvC);
}

inline tpii _calcBW(string & guess, string & correct) {
    // return calcBW(guess, correct);
    cout << guess << endl;
    fflush(stdout);

    string bw;
    cin >> bw;

    return mp((int) bw [0] - '0', (int) bw [1] - '0');
}

inline void applyGuess(string & guess, tpii & score) {
    // cout << "Guess: " << guess << endl;

    set<string>::iterator it;
    vector<string> toRemove;

    for (it = S.begin (); it != S.end (); ++ it) {
        string sit = * it;

        // calc score
        tpii score2 = calcBW(sit, guess);

        // how many possibilities in S would be eliminated
        if (score.first != score2.first || score.second != score2.second) {
            toRemove.pb(* it);
        }
    }

    int nr = csize (toRemove);
    _forn (i, 0, nr) {
        S.erase (toRemove [i]);
    }
}

inline bool isValid (string & guess) {
    _forn(i, 0, 4)
        _forn(j, i + 1, 4)
              if (guess [i] == guess [j]) return false;
    return true;
}

string genGuess() {
    int bestG = -1;
    string bestGuess = "";

    vector<string> buff;
    int nb = S.size();
    buff.reserve (nb);

    set< string >::iterator _it;
    for (_it = S.begin (); _it != S.end (); ++ _it) {
        buff.pb(* _it);
    }

    // For each possible guess
    for (int ii = 0; ii < nS; ++ ii) {
        // guess
        string pbsGuess = _S [ii];

        // for each possible colored/white peg score
        int bestS = INF;
        _forn(p, 0, 14) {
            // set< string >::iterator it;
            int badK = 0;

            for (int jj = 0; jj < nb; ++ jj) {
                // calc score
                string sit = buff [jj];

                tpii score = calcBW (sit, pbsGuess);

                // how many possibilities in S would be eliminated
                if (score.first != pbs[p][0] || score.second != pbs[p][1]) ++ badK;
            }

            // The score of a guess is the minimum number
            // of possibilities it might eliminate from S.
            bestS = min (bestS, badK);
        }

        if (bestS > bestG) {
            bestG = bestS;
            bestGuess = pbsGuess;
        } else if (bestS == bestG && contain (S, pbsGuess)) {
            bestGuess = pbsGuess;
        }
    }

    return bestGuess;
}

void genS() {
    _forn(a, 0, 10)
        _forn(b, 0, 10)
            _forn(c, 0, 10)
                _forn(d, 0, 10) {
                    // guess
                    string pbsGuess = "";
                    pbsGuess += char (a + '0');
                    pbsGuess += char (b + '0');
                    pbsGuess += char (c + '0');
                    pbsGuess += char (d + '0');

                    if (! isValid (pbsGuess)) continue;

                    // S
                    S.insert (pbsGuess);
                    _S.pb(pbsGuess);
                }

    nS = (int) _S.size();


}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>

    // getline(cin, answer);
    // answer = "4590";

    genS ();

    string firstAttempt = "1234";
    tpii score = _calcBW (firstAttempt, answer);
    applyGuess (firstAttempt, score);
    if (4 == score.first && 0 == score.second) {
        return 0;
    }

    string secondAttempt = "4567";
    score = _calcBW (secondAttempt, answer);
    applyGuess (secondAttempt, score);
    if (4 == score.first && 0 == score.second) {
        return 0;
    }

    secondAttempt = "3480";
    score = _calcBW (secondAttempt, answer);
    applyGuess (secondAttempt, score);
    if (4 == score.first && 0 == score.second) {
        return 0;
    }

    secondAttempt = "6043";
    score = _calcBW (secondAttempt, answer);
    applyGuess (secondAttempt, score);
    if (4 == score.first && 0 == score.second) {
        return 0;
    }

    // int Nnn = S.size();
    while (true) {
        string guess = genGuess ();
        score = _calcBW (guess, answer);
        applyGuess (guess, score);
        if (4 == score.first && 0 == score.second) break;
    }

    // CODE AREA <=

    return 0;
}