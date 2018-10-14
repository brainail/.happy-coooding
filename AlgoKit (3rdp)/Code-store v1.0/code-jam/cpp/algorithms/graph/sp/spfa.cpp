// Single Source Shortest Path
// SPFA: Shortest Path Faster Algorithm

// PSEUDO CODE
INITIALIZE-SINGLE-SOURCE(G, s)
1  for each vertex v in V[G]
2       do d[v] = oo
3          prev[v] = NIL
4  d[s] = 0

RELAX(u, v, w)
1  if d[v] > d[u] + w(u, v)
2     then d[v] = d[u] + w(u, v)
3          prev[v] = u


SPFA(G, w, s)
1	INITIALIZE-SINGLE-SOURCE(G, s);
2	INITIALIZE-QUEUE(Q);
3	ENQUEUE(Q, s);
4	while NOT EMPTY(Q)
5		do u = DEQUEUE(Q);
6			for each edge (u, v) in E[G]
7				do tmp = d[v]
8					RELAX(u, v, w);
9					if (d[v] < tmp && v not in Q)
10						ENQUEUE(Q, v);


// CPP CODE
int spfa(int src, int dst, int nodes){
	vector<bool> isInQueue(nodes, false);
	vector<int> dist(nodes, 0x3fffffff);
	queue<int> que;
	int u, v, w;

	que.push(src);
	dist[src] = 0;
	isInQueue[src] = true;
	while (!que.empty()){
		u = que.front();
		que.pop();
		isInQueue[u] = false;
		for (int j = 0; j < adj[u].size(); j++){
			v = adj[u][j].first;
			w = adj[u][j].second;
			if (dist[u] + w < dist[v] && !isInQueue[v]){
				dist[v] = dist[u] + w;
				que.push(v);
			}
		}
	}
	return dist[dst];
}

