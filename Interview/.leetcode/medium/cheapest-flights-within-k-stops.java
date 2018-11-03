/**
 * There are n cities connected by m flights. Each fight starts from city u and
 * arrives at v with a price w.
 * 
 * Now given all the cities and flights, together with starting city src and the
 * destination dst, your task is to find the cheapest price from src to dst with
 * up to k stops. If there is no such route, output -1.
 * 
 * Example 1: Input: n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]] src = 0, dst
 * = 2, k = 1 Output: 200
 */

class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        ArrayList<Edge>[] edges = new ArrayList[n];
        for (int i = 0; i < n; ++i)
            edges[i] = new ArrayList<Edge>();
        for (int[] flight : flights)
            edges[flight[0]].add(new Edge(flight[1], flight[2]));
        int[] dist = new int[n];
        int[] distNext = new int[n];
        final int INF = (int) 1e9;
        Arrays.fill(dist, INF);
        dist[src] = 0;
        for (int stops = 0; stops <= k; ++stops) {
            System.arraycopy(dist, 0, distNext, 0, n);
            for (int u = 0; u < n; ++u)
                if (dist[u] < INF)
                    for (Edge edge : edges[u])
                        distNext[edge.to] = Math.min(distNext[edge.to], dist[u] + edge.cost);
            System.arraycopy(distNext, 0, dist, 0, n);
        }
        return dist[dst] < INF ? dist[dst] : -1;
    }

    private class Edge {
        public final int to;
        public final int cost;

        public Edge(int to, int cost) {
            this.to = to;
            this.cost = cost;
        }
    }
}
