// INCLUDES
#include <functional>
#include <algorithm>
#include <utility>
#include <cassert>

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>

#include <cstring>
#include <string>

#include <vector>
#include <map>
using namespace std;

// TYPEDEFS
typedef pair < int, int > PII;

// DEFINES
#define FORN(index, start, end) for (int index = (int) (start); index <= (int) (end); ++ index)
#define ALL(box) box.begin(), box.end()
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)
#define CONTAINS(container, key) (container.find(key) != container.end())
#define MSG(who) cout << #who << " = " << who << endl;

// CONSTS
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES

// MY
bool ** edge;
int nSocial;
map<string, int> emailsMapping;
vector<string> emails;
vector<PII> actions;
vector<string> clusters;

void addCluster (int * clique, int nClique) {
    if (nClique < 3) return;

    vector<string> clusterEmails;
    clusterEmails.clear ();
    clusterEmails.reserve (32);

    for (int i = 0; i < nClique; ++ i) clusterEmails.PB (emails [clique [i]]);
    sort (ALL (clusterEmails));

    string cluster = "";
    for (int i = 0; i < nClique; ++ i) {
        cluster += clusterEmails [i];
        if (i < nClique - 1) cluster += ", ";
    }

    clusters.PB (cluster);
}

void bkv2 (int * clique, int nClique, int * oldSet, int ne, int ce) {
    int * newSet = (int *) malloc (ce * sizeof (int));
    int nod, fixp, newne, newce, i, j, count, pos, p, s, sel, minnod;

    minnod = ce, nod = 0;

    // Determine each counter value and look for minimum
    for (i = 0 ; i < ce && 0 != minnod; ++ i) {
        p = oldSet [i], count = 0;

        // Count disconnections
        for (j = ne; j < ce && count < minnod; ++ j)
            if (!(edge [p][oldSet [j]]) ) {
                // Save position of potential candidate
                ++ count, pos = j;
            }

        // Test new minimum
        if (count < minnod) {
            fixp = p, minnod = count;
            if (i < ne) {
                s = pos;
            } else {
                // pre-increment
                s = i, nod = 1;
            }
        }
    }

    // If fixed point initially chosen from candidates then
    // number of diconnections will be preincreased by one
    for (nod = minnod + nod; nod >= 1; -- nod) {
        // Interchange
        p = oldSet [s], oldSet [s] = oldSet [ne], sel = oldSet [ne] = p;

        // Fill new set "not"
        newne = 0;
        for (i = 0 ; i < ne ; ++ i)
            if (edge [sel][oldSet [i]]) newSet [newne ++] = oldSet [i];

        // Fill new set "cand"
        newce = newne;
        for (i = ne + 1; i < ce; ++ i)
            if (edge [sel][oldSet [i]]) newSet [newce ++] = oldSet [i];

        // Add to "actual relevant nodes"
        clique [nClique ++] = sel;

        if (0 == newce) {
            // Found a max clique
            addCluster (clique, nClique);
        } else if (newne < newce) {
            bkv2 (clique, nClique, newSet, newne, newce);
        }

        // Remove from "actual relevant nodes"
        clique [-- nClique] = NULO;

        // Add to "not"
        ++ ne;
        if (nod > 1) {
            // Select a candidate disconnected to the fixed point
            for (s = ne; edge [fixp][oldSet [s]]; ++ s);
        }
    }

    free (newSet);
}

void findClusters () {
    int i;
    int * all = (int *) malloc (nSocial * sizeof (int));
    int * clique = (int *) malloc (nSocial * sizeof (int));
    for (i = 0; i < nSocial; ++ i) all [i] = i, clique [i] = NULO;
    bkv2 (clique, 0, all, 0, nSocial);
    free (all);
    free (clique);
}

int addEmail (string email) {
    int emailId = NULO;

    if (CONTAINS (emailsMapping, email)) {
        emailId = emailsMapping [email];
    } else {
        emailId = nSocial;
        emailsMapping [email] = emailId;
        ++ nSocial;
        emails.PB (email);
    }

    assert (SIZE (emails) == nSocial);

    return emailId;
}

void runSolution() {
    nSocial = 0;
    emailsMapping.clear ();
    emails.clear ();
    emails.reserve (1024);
    actions.clear ();
    actions.reserve (1024);
    clusters.clear ();
    clusters.reserve (1024);

    // Reading ...
    string testLine;
    string TAB = "\t";
    while (getline (cin, testLine)) {
        if (string::npos == testLine.find (TAB)) break;
        testLine.erase (0, testLine.find (TAB) + 1);
        if (string::npos == testLine.find (TAB)) break;
        string fromEmail = testLine.substr (0, testLine.find (TAB));
        testLine.erase (0, testLine.find (TAB) + 1);
        string toEmail = testLine;

        int fromId = addEmail (fromEmail);
        int toId = addEmail (toEmail);

        actions.PB (MP (fromId, toId));
    }

    edge = (bool **) malloc (nSocial * sizeof (bool *));
    for (int i = 0; i < nSocial; ++ i) edge [i] = (bool *) malloc (nSocial * sizeof (bool));

    for (int i = 0; i < nSocial; ++ i)
        for (int j = 0; j < nSocial; ++ j)
            edge [i][j] = (i != j) ? false : true;

    for (int i = 0; i < SIZE (actions); ++ i) {
        edge [actions [i].first][actions [i].second] = true;
    }

    for (int i = 0; i < nSocial; ++ i)
        for (int j = 0; j < nSocial; ++ j)
            if (!edge [i][j] || !edge [j][i]) {
                edge [i][j] = edge [j][i] = false;
            }

    findClusters ();

    sort (ALL (clusters));
    for (int i = 0; i < SIZE (clusters); ++ i)
        printf("%s\n", clusters [i].c_str ());

    for (int i = 0; i < nSocial; ++ i) {
        bool * array = edge [i];
        free (array);
    }
}

// MAIN
int main(int argc, char * argv []) {
    // freopen(argv [1], "r", stdin);
    freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    runSolution();
    // CODE AREA <=

    return 0;
}