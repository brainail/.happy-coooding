// INCLUDES
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

// #include <inttypes.h>
// #include <ctype.h>
using namespace std;

// TYPEDEFS
typedef long long tll;


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
#define forT(testId) int __T; scanf("%d\n", &__T); _FORN(testId, 0, __T)
#define fill(box, value) memset(box, value, sizeof(box))
#define fill0(box) memset(box, 0, sizeof(box))
#define fillf(box) memset(box, false, sizeof(box))
#define fill_(box) memset(box, -1, sizeof(box))
#define all(box) box.begin(), box.end()
#define rall(box) box.rbegin(), box.rend()
#define csize(box) ((int) (box.size()))
#define clen(box) ((int) (box.length()))
#define mp(firstItem, secondItem) make_pair(firstItem, secondItem)
#define debug(who) cout << #who << " = " << who << endl;
#define debug2(who, who2) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl;
#define debug3(who, who2, who3) cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl;
#define debugp(who) cout << #who << " = (" << who.first << ", " << who.second << ")" << endl;
#define endl '\n'

// CONSTS
const int INF = 1000000000;
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES
// ...

// INLINES
inline bool isUpper(char C) { return C >= 'A' && C <= 'Z'; }
inline bool isLower(char C) { return C >= 'a' && C <= 'z'; }
inline bool isLetter(char C) { return isUpper(C) || isLower(C); }
inline int toI(char C) { return isUpper(C) ? (int) (C - 'A') : (isLower(C) ? (int) (C - 'a') : -1); }
inline bool isDigit(char C) { return C >= '0' && C <= '9'; }
inline char toLower(char C) { return (isUpper(C)) ? (C + 32) : C; }
inline char toUpper(char C) { return (isLower(C)) ? (C - 32) : C; }
inline int toInt(string S) { int value; istringstream iss(S); iss >> value; return value; }
inline double toF(string S) { double value; istringstream iss(S); iss >> value; return value; }

// MY
class AhoCorasick {
    public: 
        // sum of words' length
        enum {MAXLW = 10000 + 10};
        // length of the required output
        enum {MAXLOUT = 1000 + 10};
        // 'a'..'z' or more ...
        enum {MAXCH = 26};
        // root vertex
        enum {ROOT = 1};

    public:
        // trie for aho
        int ahoTrie [MAXLW][MAXCH];
        // prefix foo
        int link [MAXLW];
        // vertex
        int N;

        // word cost. 
        int cost [MAXLW];

        // dp for cost
        int dp [MAXLOUT][MAXLW];
        // good vertex
        bool good [MAXLOUT][MAXLW];
        // ancestors
        int prevVer [MAXLOUT][MAXLW];
        // ancestors (next char)
        int prevCh [MAXLOUT][MAXLW];

    public:
        AhoCorasick() {
            N = ROOT;
            fill0(ahoTrie);
            fill0(cost);
        }

        void add(const string & item, const int & itemCost) {
            int current = ROOT;

            _forn(i, 0, clen(item)) {
                int ch = toI(item [i]);
                if (ahoTrie [current][ch] > 0) {
                    current = ahoTrie [current][ch];
                } else {
                    ahoTrie [current][ch] = ++ N, current = N;
                }
            }

            cost [current] += itemCost;
        }

        void build() {
            fill0(link);

            queue<int> q;
            q.push(ROOT);

            _forn(ch, 0, MAXCH) ahoTrie [0][ch] = ROOT;

            while (! q.empty()) {
                int current = q.front();
                q.pop();

                _forn(ch, 0, MAXCH) 
                    if (ahoTrie [current][ch] > 0) {
                        int prefv = link [current];
                        while (! (ahoTrie [prefv][ch] > 0)) prefv = link [prefv];
                        link [ahoTrie [current][ch]] = ahoTrie [prefv][ch];
                        cost [ahoTrie [current][ch]] += cost [ahoTrie [prefv][ch]];
                        q.push(ahoTrie [current][ch]);
                    }

                _forn(ch, 0, MAXCH) 
                    if (! (ahoTrie [current][ch] > 0)) {
                        ahoTrie [current][ch] = ahoTrie [link [current]][ch];    
                    }
            }
        }

        pair<int, string> calcCost(const int outLen) {
            fill_(dp);
            dp [0][ROOT] = 0;

            _forn(curLen, 0, outLen) 
                forn(curVer, ROOT, N)
                    if (dp [curLen][curVer] >= 0) {
                        _forn(ch, 0, MAXCH) {
                            int nextVer = ahoTrie [curVer][ch];
                            if (dp [curLen][curVer] + cost [nextVer] > dp [curLen + 1][nextVer]) {
                                dp [curLen + 1][nextVer] = dp [curLen][curVer] + cost [nextVer];    
                            }
                        }
                    }

            pair<int, string> bestResult = mp(0, "");
            forn(curVer, ROOT, N) bestResult.first = max(bestResult.first, dp [outLen][curVer]);

            fillf(good);
            forn(curVer, ROOT, N) good [outLen][curVer] = (dp [outLen][curVer] == bestResult.first);
            
            fill_(prevVer);
            fill_(prevCh);
            fordn(curLen, outLen - 1, 0)
                forn(curVer, ROOT, N)
                    _forn(ch, 0, MAXCH) {
                        int nextVer = ahoTrie [curVer][ch];
                        if (good [curLen + 1][nextVer]) {
                            if (dp [curLen][curVer] + cost [nextVer] == dp [curLen + 1][nextVer]) {
                                good [curLen][curVer] = true;
                                prevVer [curLen][curVer] = nextVer;
                                prevCh [curLen][curVer] = ch;
                                break;
                            }
                        }
                    }

            int curVer = ROOT;
            _forn(curLen, 0, outLen) {
                bestResult.second += (char) ('a' + prevCh [curLen][curVer]);
                curVer = prevVer [curLen][curVer];
            }

            return bestResult;
        }

};

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    AhoCorasick * testCase;
    pair<int, string> bestResult;

    testCase = new AhoCorasick();
    testCase->add("a", 1);
    testCase->add("b", 1);
    testCase->add("ab", 3);
    testCase->add("caa", 6);
    testCase->build();
    bestResult = testCase->calcCost(4);
    assert(12 == bestResult.first);
    debugp(bestResult);

    testCase = new AhoCorasick();
    testCase->add("a", 1);
    testCase->add("b", 1);
    testCase->add("ab", 4);
    testCase->add("bac", 8);
    testCase->build();
    bestResult = testCase->calcCost(7);
    assert(25 == bestResult.first);
    debugp(bestResult);
    // CODE AREA <=

    return 0;
}