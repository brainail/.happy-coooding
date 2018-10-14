#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <map>
#include <cstdio>
#include <cstring>
#include <utility>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

typedef long long LL;

// Const: input file name
const string INPUT_FILE = "input.txt";

// Const: output file name
const string OUTPUT_FILE = "output.txt";

// The class which represents some graph
template <typename T> class Graph {

public:

    // empty value
    #define EMPTY (-1)

    // maximum number of edges
    #define MAX_EDGE (1000000 + 10)

    // maximum number of vertices
    #define MAX_VERT (100000 + 10)

    // The class which represents some edge (directed)
    class Edge {

    private:

        // "from" vertex
        int _mFrom;

        // "to" vertex
        int _mTo;

        // "cost" of edge
        T _mCost;

    public:

        Edge(): _mFrom(EMPTY), _mTo(EMPTY), _mCost(EMPTY) {}

        Edge(int from, int to, T cost): _mFrom(from), _mTo(to), _mCost(cost) {}

    public:

        void setCost(T cost) { 
            _mCost = cost;
        }

        void setFrom(int from) {
            _mFrom = from;
        }

        void setTo(int to) {
            _mTo = to;
        }

        int getFrom() {
            return from;
        }

        int getTo() {
            return to;
        }

        T getCost() {
            return cost;
        }

        // returns a full key of this edge
        pair< pair< int, int >, T > getFullKey() {
            return make_pair(make_pair(_mFrom, _mTo), _mCost);
        }

        // returns a key of this edge
        pair< int, int > getKey() {
            return make_pair(_mFrom, _mTo);
        }

        // prints this edge
        void print() {
            cout << _mFrom << " == [" << _mCost << "] ==> " << _mTo << endl;
        }

    };

private:

    // number of vertices
    int mV;

    // number of edges
    int mE;
    
    // index of last edge for a specific vertex
    vector<int> mLastEdge;
    
    // index of next edge for a specific edge
    vector<int> mNextEdge;
    
    // list of similar edges for a specific edge
    vector< vector< Edge > > mEdge;

    // mapping (edge => id)
    map< pair< pair< int, int >, T >, pair< pair< int, int >, int > > mEdgesFullMapping;
    map< pair< int, int >, int > mEdgesMapping;

    // mapping iterators typedefs
    #define efm_it map< pair< pair< int, int >, T >, pair< pair< int, int >, int > >::iterator
    #define em_it map< pair< int, int >, int >::iterator

public:

    Graph(int V): mV(V), mE(0) {

        assert(V >= 0 && V < MAX_VERT);

        mLastEdge.resize(V);
        mLastEdge.assign(V, EMPTY);

        mNextEdge.reserve(MAX_EDGE);

        mEdge.reserve(MAX_EDGE);

    }

    // adds an edge to this graph
    void addEdge(int from, int to, T cost) {

        assert(from >= 0 && from < mV);
        assert(to >= 0 && to < mV);

        Edge edge = Edge(from, to, cost);

        efm_it itf;
        if ((itf = mEdgesFullMapping.find(edge.getFullKey())) != mEdgesFullMapping.end()) {
            ++ itf->second.second;
            return;
        } else {
            em_it it;
            if ((it = mEdgesMapping.find(edge.getKey())) != mEdgesMapping.end()) {
                mEdgesFullMapping[edge.getFullKey()] = make_pair(make_pair(it->second, mEdge[it->second].size()), 1);
            } else {
                mEdgesFullMapping[edge.getFullKey()] = make_pair(make_pair(mE, 0), 1);
            }
        }

        em_it it;
        if ((it = mEdgesMapping.find(edge.getKey())) != mEdgesMapping.end()) {
            mEdge[it->second].push_back(edge);
            return;
        }

        mNextEdge.push_back(mLastEdge[from]); 
        mEdge.push_back(vector<Edge> ());
        mEdge.back().push_back(edge);
        mEdgesMapping[edge.getKey()] = mE;
        mLastEdge[from] = mE; 
        ++ mE;

    }

    // adds an edge to this graph with the "revert" option
    void addEdge(int from, int to, T cost, bool revert) {
        addEdge(from, to, cost);
        if (revert) {
            addEdge(to, from, cost);
        }
    }

    // removes the edge from graph
    void eraseEdge(Edge edge) {
        efm_it it;         
        if ((it = mEdgesFullMapping.find(edge.getFullKey())) != mEdgesFullMapping.end()) {
            -- it->second.second;
            if (0 == it->second.second) {
                mEdge[it->second.first.first].erase(mEdge[it->second.first.first].begin() + it->second.first.second);
                mEdgesFullMapping.erase(it);
            }
        }
    }

    // prints graph
    void print() {
        for (int vIndex = 0; vIndex < mV; ++ vIndex) {
            for(int eIndex = mLastEdge[vIndex]; eIndex >= 0; eIndex = mNextEdge[eIndex]) {
                for (int kIndex = 0; kIndex < mEdge[eIndex].size(); ++ kIndex) {
                    mEdge[eIndex].at(kIndex).print();
                }
            }
        }

        cout << endl;
    }

};

int main() {

    // input & output file
    freopen( INPUT_FILE.c_str(), "r", stdin );
    freopen( OUTPUT_FILE.c_str(), "w", stdout );

    Graph<LL> g = Graph<LL> (100001);

    for (int i = 1; i <= 100000; ++ i) {
        g.addEdge(0, i, i);
        g.addEdge(i, 0, i);
        g.addEdge(0, i, i, true);
        g.addEdge(i, 0, i, true);
    }

    return 0;

}