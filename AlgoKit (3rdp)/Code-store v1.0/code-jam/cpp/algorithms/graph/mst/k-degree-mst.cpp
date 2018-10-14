/*
 *	Problem:  POJ 1639
 *	Source:   East Central North America 2000
 *	Algorithm: Mininum K-Degree Spaning Tree
 *	    1. V[0] is the K-Degree node. Find SCC of {V1, V2 ... Vn}
 *	       If scc num m > K, the output "no solution". Else calculate
 *	       MST of every scc.
 *	    2. Find the min distance to V[0] in each scc.
 *	    3. Iteration k from m+1 to K, in each iter do:
 *		   Enum node j to V0 which is not in MST. Find the max edge
 *		   from V0 to j, this can be achived by DP.
 *		   Find the min diff = W[V0][j] - max_dist[j]. This is the 
 *		   k+1 degree MST. Then loop back to step 3.
 *		4. Output ans.
 *	Reference: wc2004, Wang Ding.
 * */

#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXNODE = 21;
const string PARK = "Park";

int N, K, M;
int graph[MAXNODE][MAXNODE], block[MAXNODE], num_block;
bool mst[MAXNODE][MAXNODE];
map< string, int > place;

void init() {
	memset(mst, 0, sizeof(mst));
	memset(graph, 0, sizeof(graph));
	place.clear();
}

void input() {
	string stra, strb;
	int a, b, i, dist;
	M = 1;
	for (i = 0; i < N; i++) {
		cin >> stra >> strb >> dist;
		
		if (stra == PARK) a = 0;
		else {
			if (!place.count(stra)) {
				a = M;
				place[stra] = M++;
			} else
				a = place[stra];
		}

		if (strb == PARK) b = 0;
		else {
			if (!place.count(strb)) {
				b = M;
				place[strb] = M++;
			} else
				b = place[strb];
		}
		
		graph[a][b] = graph[b][a] = dist;
	}
	cin >> K;
}

void dfs_scc(int g[MAXNODE][MAXNODE], int u, bool *vist, const int scc_cnt) {
	if (vist[u]) return;
	vist[u] = true;
	block[u] = scc_cnt;
	for (int v = 1; v < M; v++) if (g[u][v] && !vist[v]) {
		dfs_scc(g, v, vist, scc_cnt);
	}
}

void scc() {
	int i, j;
	int g[MAXNODE][MAXNODE];
	bool vist[MAXNODE];
	memset(vist, 0, sizeof(vist));
	
	// delete edge related to Park.
	for (i = 1; i < M; i++)
		for (j = 1; j < M; j++)
			g[i][j] = graph[i][j];

	// find all block
	for (i = 1, num_block = 1; i < M; i++) {
		dfs_scc(g, i, vist, num_block);
		num_block++;
	}
}

int prim(int g[MAXNODE][MAXNODE]) {
	int u, v, total = 0;
	vector<int> dist(M, INT_MAX);
	vector<bool> visit(M, false);
	vector<int> father(M);
	priority_queue< pair<int, int> > pq;
	dist[0] = 0;
	pq.push(make_pair(-dist[0], 0));

	while (!pq.empty()) {
		pair<int, int> p = pq.top();
		pq.pop();
		u = p.second;
		if (visit[u]) continue;
		visit[u] = true;
		for (v = 1; v < M; v++) if (g[u][v] && !visit[v]) {
			if (g[u][v] < dist[v]) {
				dist[v] = g[u][v];
				father[v] = u;
				pq.push(make_pair(-dist[v], v));
			}
		}
	}

	for (u = 1; u < M; u++) {
		v = father[u];
		mst[u][v] = mst[v][u] = true;
		total += g[u][v];
	}

	return total;
}

int mst_prim() {
	int i, j;
	int g[MAXNODE][MAXNODE];
	memset(g, 0, sizeof(g));
	for (i = 1; i < num_block; i++) {
		int min_dist = INT_MAX, k = -1;
		for (j = 1; j < M; j++) {
			if (block[j] == i && graph[0][j] && graph[0][j] < min_dist) {
				min_dist = graph[0][j];
				k = j;
			}
		}
		g[0][k] = g[k][0] = graph[0][k];
	}
	for (i = 1; i < M; i++)
		for (j = 1; j < M; j++)
			g[i][j] = graph[i][j];
	return prim(g);
}

void dfs(int u, int parent, int *max_dist, bool *vist, vector< pair<int, int> > &path) {
	vist[u] = true;
	if (u == 0 || parent == 0) {
		max_dist[u] = -INT_MAX;
		path[u] = make_pair(0, 0);
	} else {
		if (graph[u][parent] > max_dist[parent]) {
			max_dist[u] = graph[u][parent];
			path[u] = make_pair(u, parent);
		} else {
			max_dist[u] = max_dist[parent];
			path[u] = path[parent];
		}
	}
	for (int v = 0; v < M; v++) if (mst[u][v] && !vist[v]) {
		dfs(v, u, max_dist, vist, path);
	}
}

void solve() {
	// find strongly connected component(scc).
	scc();
	// find mst with m-degree tree. (m is the num of scc)
	int ans = mst_prim();
	// dp state. it is the longest edge from V0 to Vi.
	int max_dist[MAXNODE];
	bool vist[MAXNODE];
	vector< pair<int, int> > path(MAXNODE);
	memset(vist, 0, sizeof(vist));
	dfs(0, -1, max_dist, vist, path);

	int i, j, k, e;
	for (i = 1, k = 0; i < M; i++) if (mst[0][i]) k++;

	// begin mst iteration.
	for (; k < K; k++) {
		j = INT_MAX, e = -1;
		// find the min diff value to the current k-mst.
		for (i = 1; i < M; i++) if (graph[0][i] && !mst[0][i]) {
			if (graph[0][i] - max_dist[i] < j) {
				j = graph[0][i] - max_dist[i];
				e = i;
			}
		}
		// can not get a more optimal mst, then break.
		if (j >= 0) break;
		ans += j;
		pair<int, int> p = path[e];
		// update the k+1 mst.
		mst[p.first][p.second] = mst[p.second][p.first] = 0;
		mst[0][e] = mst[e][0] = true;
		memset(vist, 0, sizeof(vist));
		dfs(0, -1, max_dist, vist, path);
	}

	cout << "Total miles driven: " << ans << endl;
}

int main() {
	while (cin >> N) {
		init();
		input();
		solve();
	}
return 0;
}

