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
const int NULO = -1;

const string IDE_PATH
        = "/Users/brainail/DevProjects/Privacy/Programming/Happy-coding/Competitions/_IDE/";
const string INPUT_FILE
        = IDE_PATH + "RCC/2016/Round3B/input.txt";
const string OUTPUT_FILE
        = IDE_PATH + "RCC/2016/Round3B/output.txt";

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
#define root 0
#define N 100000 + 10
#define LN 18
#define is_vhld true

vector <int> adj[N], costs[N], indexx[N];
int baseArray[N], ptr, n;
int chainNo, chainInd[N], chainHead[N], posInBase[N];
int depth[N], pa[LN][N], otherEnd[N], subsize[N];

int tsum[4 * N];
int tadd[4 * N];

void _push(int node, int left, int right) {
    tsum[node] += tadd[node] * (right - left + 1);
    if (left < right) {
        tadd[node * 2] += tadd[node];
        tadd[node * 2 + 1] += tadd[node];
    }
    tadd[node] = 0;
}

void _pop(int node, int left, int right) {
    int mid = (left + right) >> 1;
    tsum[node] = tsum[node * 2] + tadd[node * 2] * (mid - left + 1);
    tsum[node] += tsum[node * 2 + 1] + tadd[node * 2 + 1] * (right - mid);
}

void _add(int a, int b, int value, int node = 1, int left = 0, int right = N - 1) {
    _push(node, left, right);
    if (left >= a && right <= b) {
        tadd[node] += value;
        return;
    }
    int mid = (left + right) >> 1;
    if (a <= mid) _add(a, b, value, node * 2, left, mid);
    if (b > mid) _add(a, b, value, node * 2 + 1, mid + 1, right);
    _pop(node, left, right);
}

int _sum(int a, int b, int node = 1, int left = 0, int right = N - 1) {
    _push(node, left, right);
    if (left >= a && right <= b) return tsum[node];
    int mid = (left + right) >> 1;
    int res = 0;
    if (a <= mid) res += _sum(a, b, node * 2, left, mid);
    if (b > mid) res += _sum(a, b, node * 2 + 1, mid + 1, right);
    _pop(node, left, right);
    return res;
}

int _get(int i, int node = 1, int left = 0, int right = N - 1) {
    _push(node, left, right);
    if (left == right) return tsum[node];
    int mid = (left + right) >> 1;
    int res = i <= mid ? _get(i, node * 2, left, mid) : _get(i, node * 2 + 1, mid + 1, right);
    _pop(node, left, right);
    return res;
}

void _set(int i, int value) {
    _add(i, i, -_get(i) + value);
}

/*
 * update_tree:
 * Point update. Update a single element of the segment tree.
 */
//void update_tree(int cur, int s, int e, int x, int val) {
//    if(s > x || e <= x) return;
//    if(s == x && s == e-1) {
//        st[cur] += val;
//        return;
//    }
//    int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
//    update_tree(c1, s, m, x, val);
//    update_tree(c2, m, e, x, val);
//    st[cur] = st[c1] + st[c2];
//}

/*
 * query_tree:
 * Given S and E, it will return the maximum value in the range [S,E)
 */
//void query_tree(int cur, int s, int e, int S, int E) {
//    if(s >= E || e <= S) {
//        qt[cur] = 0;
//        return;
//    }
//    if(s >= S && e <= E) {
//        qt[cur] = st[cur];
//        return;
//    }
//    int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
//    query_tree(c1, s, m, S, E);
//    query_tree(c2, m, e, S, E);
//    qt[cur] = qt[c1] + qt[c2];
//}

/*
 * query_up:
 * It takes two nodes u and v, condition is that v is an ancestor of u
 * We query the chain in which u is present till chain head, then move to next chain up
 * We do that way till u and v are in the same chain, we query for that part of chain and break
 */

int query_up(int u, int v) {
    // printf("query_up, u = %d, v = %d\n", u + 1, v + 1);

    if (u == v && !is_vhld) return 0;

    if (u == v) {
        return _get(posInBase[u]);
    }

    int uchain, vchain = chainInd[v], ans = 0;
    // uchain and vchain are chain numbers of u and v
    while(1) {
        uchain = chainInd[u];
        if(uchain == vchain) {
            // Both u and v are in the same chain, so we need to query from u to v, update answer and break.
            // We break because we came from u up till v, we are done
            if (u==v && !is_vhld) break;
            int tt = _sum(posInBase[v]+(is_vhld ? 0 : 1), posInBase[u]);
            // Above is call to segment tree query function
            ans += tt; // Update answer
            break;
        }
        int tt = _sum(posInBase[chainHead[uchain]], posInBase[u]);
        // Above is call to segment tree query function. We do from chainHead of u till u. That is the whole chain from
        // start till head. We then update the answer
        ans += tt;
        u = chainHead[uchain]; // move u to u's chainHead
        u = pa[0][u]; //Then move to its parent, that means we changed chains
    }
    return ans;
}

/*
 * LCA:
 * Takes two nodes u, v and returns Lowest Common Ancestor of u, v
 */
int LCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];

    for(int i=0; i<LN; i++)
        if((diff >> i) & 1) u = pa[i][u];

    if (u == v) return u;

    for(int i=LN-1; i>=0; i--)
        if(pa[i][u] != pa[i][v]) {
            u = pa[i][u], v = pa[i][v];
        }

    return pa[0][u];
}

int query(int u, int v) {
    /*
     * We have a query from u to v, we break it into two queries, u to LCA(u,v) and LCA(u,v) to v
     */
    int lca = LCA(u, v);
    int ans = query_up(u, lca); // One part of path
    int temp = query_up(v, lca); // another part of path
    return ans + temp;
}

void vchange(int i, int val) {
    int u = i;
    _add(posInBase[u], posInBase[u], val);
}

/*
 * change:
 * We just need to find its position in segment tree and update it
 */
void echange(int i, int val) {
    int u = otherEnd[i];
    vchange(u, val);
    // update_tree(1, 0, ptr, posInBase[u], val);
}

/*
 * Actual HL-Decomposition part
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size.
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */
void HLD(int curNode, int cost, int prev) {
    if(chainHead[chainNo] == -1) {
        chainHead[chainNo] = curNode; // Assign chain head
    }

    chainInd[curNode] = chainNo;
    posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
    baseArray[ptr++] = cost;

    int sc = -1, ncost;

    // Loop to find special child
    for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
            if(sc == -1 || subsize[sc] < subsize[adj[curNode][i]]) {
                sc = adj[curNode][i];
                ncost = costs[curNode][i];
            }
        }

    if(sc != -1) {
        // Expand the chain
        HLD(sc, ncost, curNode);
    }

    for(int i=0; i<adj[curNode].size(); i++) if(adj[curNode][i] != prev) {
            if(sc != adj[curNode][i]) {
                // New chains at each normal node
                chainNo++;
                HLD(adj[curNode][i], costs[curNode][i], curNode);
            }
        }
}

/*
 * dfs used to set parent of a node, depth of a node, subtree size of a node
 */
void dfs(int cur, int prev, int _depth=0) {
    pa[0][cur] = prev;
    depth[cur] = _depth;
    subsize[cur] = 1;
    for(int i=0; i<adj[cur].size(); i++)
        if(adj[cur][i] != prev) {
            otherEnd[indexx[cur][i]] = adj[cur][i];
            dfs(adj[cur][i], cur, _depth+1);
            subsize[cur] += subsize[adj[cur][i]];
        }
}

void prepare() {
    ptr = 0;
    chainNo = 0;

    for(int i=0; i<N; i++) {
        adj[i].clear();
        costs[i].clear();
        indexx[i].clear();
        chainHead[i] = -1;
        for(int j=0; j<LN; j++) pa[j][i] = -1;
    }
}

void read() {
    scanf("%d\n", &n);

    for(int i=1; i<n; i++) {
        int u, v, c = 0;
        // scanf("%d %d %d", &u, &v, &c);
        scanf("%d", &u);
        u--; v = i; c = 1;
        adj[u].push_back(v);
        costs[u].push_back(c);
        indexx[u].push_back(i-1);
        adj[v].push_back(u);
        costs[v].push_back(c);
        indexx[v].push_back(i-1);
    }
}

void build() {
    dfs(root, -1); // We set up subsize, depth and parent for each node
    HLD(root, 0, -1); // We decomposed the tree and created baseArray
    ///make_tree(1, 0, ptr); // We use baseArray and construct the needed segment tree
    for (int i = 0; i < ptr; ++i) _set(i, baseArray[i]);

    // Lca
    for(int i=1; i<LN; i++)
        for(int j=0; j<n; j++)
            if(pa[i-1][j] != -1) pa[i][j] = pa[i-1][pa[i-1][j]];
}

void solve() {
    int Q;
    scanf("%d", &Q);

    for (int q = 0; q < Q; ++ q) {
        int type, x, y;

        scanf("%d %d", &type, &x);

        // add
        if (type == 2) {
            vchange(x-1, -1);
        }

        // max
        if (type == 1) {
            scanf("%d", &y);
            printf("%d\n", query(x-1, y-1));
        }
    }
}

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    // freopen(INPUT_FILE.c_str(), "r", stdin);
    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    prepare();
    read();
    build();

    // printf("chainNo = %d\n", chainNo);
    // for(int u = 0; u < n; ++ u) printf("u = %d, chainId = %d\n", u + 1, chainInd [u]);
    // for(int u = 0; u < n; ++ u) printf("u = %d, posInBase = %d\n", u + 1, posInBase [u]);

    solve();

    // CODE AREA <=

    return 0;
}