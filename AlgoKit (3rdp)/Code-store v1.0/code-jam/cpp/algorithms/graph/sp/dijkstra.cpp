// Single Source Shortest Path
// Dijkstra + Heap.

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

DIJKSTRA(G, w, s)
1  INITIALIZE-SINGLE-SOURCE(G, s)
2  S = NULL
3  Q = V[G]
4  while Q NOT EMPTY
5      do u = EXTRACT-MIN(Q)
6         S = S | {u}
7         for each vertex v in Adj[u]
8             do RELAX(u, v, w)


// CPP CODE
void dijkstra(){
	priority_queue< pair<int, int> > pq;
	vector<bool> visit(N, false);
	vector<int>  dist(N, INT_MAX);
	int u, v;
	dist[0] = 0;
	pq.push(make_pair(dist[0], 0));
	while (!pq.empty()) {
		pair<int, int> p = pq.top();
		pq.pop();
		u = p.second;
		if (visit[u]) continue;
		visit[u] = true;
		for (v = 0; v < N; v++) if (!visit[v]){
			if (dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
				pq.push(make_pair(-dist[v], v));
			}
		}
	}
}

