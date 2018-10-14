// All pair shortest path problem: Floyd-Warshall Algorithm.

// Algorithm:
// For every pair [i, j], suppose from i to j using intermediate
// points set {1, 2 ... k-1}. Then
// 1) k is not an intermediate point. 
//		Then a shortest path from vertex i to vertex j with all 
//		intermediate vertices in the set {1, 2,..., k - 1} is also 
//		a shortest path from i to j with all intermediate vertices 
//		in the set {1, 2,..., k}.
// 2) k is an intermediate vertex of path p,
//		then we break p down into i->k->j, by p1 and p2. p1 is a 
//		shortest path from i to k with all intermediate vertices in 
//		the set {1, 2,..., k-1}. Similarly, p2 is a shortest path 
//		from vertex k to vertex j with all intermediate vertices in 
//		the set {1, 2,..., k-1}.
// 
// If k = 0, d[k][i][j] = w[i][j].
// Else if k >= 1, d[k][i][j] = min(d[k-1][i][j], d[k-1][i][k] + d[k-1][k][j]);


// PSEUDO CODE:
FLOYD-WARSHALL(W)
1  n = rows[W]
2  D(0) = W
3  for k = 1 to n
4    do for i = 1 to n
5      do for j = 1 to n
6        do d[k][i][j] = min(d[k-1][i][j], d[k-1][i][k] + d[k-1][k][j]);
7  return D(n)

Calculate prev[]:
if (i == j || w[i][j] == oo) prev[0][i][j] = NIL
if (i != j && w[i][j] <  oo) prev[0][i][j] = i;

if (d[k-1][i][j] <= d[k-1][i][k] + d[k-1][k][j]) prev[k][i][j] = prev[k-1][i][j];
if (d[k-1][i][j] >  d[k-1][i][k] + d[k-1][k][j]) prev[k][i][j] = prev[k-1][k][j];


// CPP CODE:
void floyd_warshall() {
	int i, j, k;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			D[i][j] = W[i][j]; // W[i][i] = 0

	for (k = 1; k <= N; k++)
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++) 
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
}


// Transitive closure of a directed graph
// Similar to floyd-warshall algorithm.
// We define t[k][i][j] to be 1 if there exists a path in graph G 
// from vertex i to vertex j with all intermediate vertices in the 
// set {1, 2,..., k}, and 0 otherwise.


// PSEUDO CODE:
TRANSITIVE-CLOSURE(G)
 1  n = |V[G]|
 2  for i = 1 to n
 3    do for j = 1 to n
 4      do if i = j or (i, j) in E[G]
 5        then t[0][i][j] = 1;
 6        else t[0][i][j] = 0;
 7  for k = 1 to n
 8    do for i = 1 to n
 9      do for j = 1 to n
10        do t[k][i][j] = t[k-1][i][j] | (t[k-1][i][j] & t[k-1][k][j]);
11  return T(n)


