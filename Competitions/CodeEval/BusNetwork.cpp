// INCLUDES
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <iterator>
#include <queue>
#include <vector>
#include <map>
using namespace std;

// TYPEDEFS
typedef vector< vector< pair<int, int> > > Graph;

// DEFINES
#define _FORN(index, start, end) for (int index = (int) (start); index < (int) (end); ++ index)
#define ALL(box) box.begin(), box.end()
#define SIZE(box) ((int) (box.size()))
#define LENGTH(box) ((int) (box.length()))
#define MP(firstItem, secondItem) make_pair(firstItem, secondItem)
#define PB(value) push_back(value)
#define MSG(who) cout << #who << " = " << who << endl;

// CONSTS
const int INF = 1000000000;
const int NULO = -1;
const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";

// TEMPLATES

// INLINES
inline int TO_INTS(string S) { int value; istringstream iss(S); iss >> value; return value; }

// MY
const int MAX_STOP = 300 + 10;
const int MAX_ROUTE = 150 + 10;
const int MAX_GLOBAL_STOP = MAX_STOP * MAX_ROUTE;

string testLine, data;
vector< vector<int> > stopRoutes;
map<string, int> stopsIds;
vector<int> prio;
Graph G;
int Ns, Nr;

int getStopId(string stopName) {
    int result = NULO;
    map<string, int>::iterator it = stopsIds.find(stopName);

    if (it == stopsIds.end()) {
        stopsIds [stopName] = ++ Ns, result = Ns;
    } else {
        result = it->second;
    }

    return result;
}

int getGlobalStopId(int routeId, int stopId) {
    return MAX_STOP * (routeId - 1) + stopId;
}

int dijkstra(int vfrom, int vto) {
    int n = G.size();
    prio.clear(), prio.resize(n, INF);
    prio [vfrom] = 0;
    priority_queue< pair<int, int>, vector< pair<int, int> > , greater< pair<int, int> > > q;
    q.push(MP(prio [vfrom], vfrom));

    while (!q.empty()) {
        int d = q.top().first, u = q.top().second;
        q.pop();
        if (d != prio [u]) continue;
        _FORN(i, 0, SIZE(G [u])) {
            int v = G [u][i].first, nprio = prio [u] + G [u][i].second;
            if (prio [v] > nprio) {
                prio[v] = nprio;
                q.push(MP(nprio, v));
            }
        }
    }

    return prio [vto];
}

void runSolution() {
    // read testcase
    while (getline(cin, testLine)) {
        // init
        Ns = Nr = 0;
        stopsIds.clear();
        stopRoutes.clear(), stopRoutes.resize(MAX_STOP);
        G.clear(), G.resize(MAX_GLOBAL_STOP);
        istringstream sinput(testLine);

        // read from & to
        getline(sinput, data, '(');
        getline(sinput, data, ',');
        int from = getStopId(data);
        getline(sinput, data, ')');
        int to = getStopId(data);
        getline(sinput, data, ';');

        // read routes & stops
        while (getline(sinput, data, '[')) {
            if (string::npos == data.find("R")) break;

            getline(sinput, data, ']');
            assert (',' != data [LENGTH (data) - 1]);
            ++ Nr, data += ',';

            int pStop = NULO;
            string stopData = "";

            _FORN(i, 0, LENGTH(data)) {
                if (data [i] == ',') {
                    int cStop = getStopId(stopData);
                    stopRoutes [cStop].PB(Nr);

                    // edges between stops
                    if (NULO != pStop) {
                        int gFrom = getGlobalStopId(Nr, pStop), gTo = getGlobalStopId(Nr, cStop);
                        G [gFrom].PB(MP(gTo, 7)), G [gTo].PB(MP(gFrom, 7));
                    }

                    pStop = cStop, stopData = "";
                    continue;
                }

                stopData += data [i];
            }
        }

        // edges between routes
        _FORN(stopId, 1, Ns + 1) {
            int Nsr = SIZE(stopRoutes [stopId]);
            _FORN(i, 0, Nsr)
                _FORN(j, i + 1, Nsr) {
                    int rFrom = stopRoutes [stopId][i], rTo = stopRoutes [stopId][j];
                    int gFrom = getGlobalStopId(rFrom, stopId), gTo = getGlobalStopId(rTo, stopId);
                    G [gFrom].PB(MP(gTo, 12)), G [gTo].PB(MP(gFrom, 12));
                }
        }

        // edges from 0 to "from"
        int startStop = 0;
        _FORN(r, 1, Nr + 1) {
            int gFrom = startStop, gTo = getGlobalStopId(r, from);
            G [gFrom].PB(MP(gTo, 0));
        }

        // edges from "from" to "end"
        int endStop = Nr * MAX_STOP + 1;
        _FORN(r, 1, Nr + 1) {
            int gFrom = getGlobalStopId(r, to), gTo = endStop;
            G [gFrom].PB(MP(gTo, 0));
        }

        // calc
        int result = dijkstra(startStop, endStop);

        // print
        if (result < INF) {
            printf("%d\n", result);
        } else {
            printf("None\n");
        }
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