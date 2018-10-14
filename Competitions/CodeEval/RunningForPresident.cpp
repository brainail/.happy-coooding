// INCLUDES
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

// TYPEDEFS

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define ALL(box) box.begin(), box.end()
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)
#define TWOP(power) (1 << (power))

// CONSTS
const int INF = 1000000000;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }

// MY
int nIssues;
string inLine;
vector< pair<string, int> > issues;
vector< pair<int, map<string, int> > > votes;

void runSolution() {
    getline(cin, inLine, ':');
    scanf("%d\n\n", &nIssues);

    issues.clear(), issues.resize(nIssues);
    _FORN(i, 0, nIssues) {
        getline(cin, issues [i].first, ':');
        scanf("%d\n", &issues [i].second);
    }

    sort(ALL(issues));

    votes.reserve(600);
    while (true) {
        if (!getline(cin, inLine, ':')) break;
        if (string::npos == inLine.find("Votes")) break;

        map<string, int> countryIssues;
        votes.PB(MP(0, countryIssues));

        scanf("%d\n", &votes.back().first);
        int kVotes = votes.back().first;

        while (true) {
            getline(cin, inLine);
            string testLine = inLine;
            testLine.erase(std::remove(ALL(testLine), ' '), testLine.end());
            if (testLine.empty() || string::npos == testLine.find(":")) break;

            string issueName = inLine.substr(0, inLine.find(":"));
            inLine.erase(0, inLine.find(":") + 1);
            int issueVotes = TO_INTS(inLine);

            votes.back().second.insert(pair<string, int> (issueName, issueVotes));
        }
    }

    int pw [20];
    _FORN(i, 0, 20) pw [i] = TWOP(i);

    int resultIssues = INF, resultCost = INF, resultMask = 0;
    _FORN(mask, 0, pw [nIssues]) {
        int choosenIssues = 0, choosenCost = 0;

        _FORN(j, 0, nIssues)
            if ((((mask) & (pw [j])) != 0))
                ++ choosenIssues, choosenCost += issues [j].second;

        if (choosenIssues > resultIssues) continue;
        if (choosenIssues == resultIssues && choosenCost >= resultCost) continue;

        int okVotes = 0;

        _FORN(i, 0, SIZE(votes)) {
            int countryOkVotes = 0;

            _FORN(j, 0, nIssues)
                if ((((mask) & (pw [j])) != 0)) {
                    map<string, int>::iterator entry = votes [i].second.find(issues [j].first);
                    if (votes [i].second.end() != entry) countryOkVotes += entry->second;
                }

            if (countryOkVotes * 100 >= 51 * votes [i].first) okVotes += votes [i].first;
        }

        if (okVotes >= 270) {
            if (choosenIssues < resultIssues || (choosenIssues == resultIssues && choosenCost < resultCost)) {
                resultIssues = choosenIssues, resultCost = choosenCost, resultMask = mask;
            }
        }
    }

    if (INF != resultIssues) {
        _FORN(j, 0, nIssues)
            if (((((resultMask) & (pw [j])) != 0))) printf("%s\n", issues [j].first.c_str());
    }
}

// MAIN
int main(int argc, char * argv []) {
    freopen(argv [1], "r", stdin);
    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    runSolution();
    // CODE AREA <=

    return 0;
}