/**
 * In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 */
class Solution {
    int[][] p = new int[1000 + 10][2];
    boolean[] visited = new boolean[1000 + 10];

    public int[] findRedundantDirectedConnection(int[][] edges) {
        for (int i = 0; i < p.length; ++i)
            Arrays.fill(p[i], -1);
        int index = 0;
        for (int[] edge : edges) {
            if (p[edge[1]][0] != -1) return checkMaybeEdges(edges, edge, new int[] { p[edge[1]][0], edge[1] });
            p[edge[1]][0] = edge[0]; p[edge[1]][1] = index++;
        }
        Arrays.fill(visited, false);
        int u = 1;
        while (!visited[u]) { visited[u] = true; u = p[u][0]; }
        int[] ret = null;
        index = Integer.MIN_VALUE;
        Arrays.fill(visited, false);
        while (!visited[u]) {
            visited[u] = true;
            if (p[u][1] > index) {
                index = p[u][1]; ret = new int[] { p[u][0], u };
            }
            u = p[u][0];
        }
        return ret;
    }

    private int[] checkMaybeEdges(int[][] edges, int[] edgeA, int[] edgeB) {
        ArrayList<Integer>[] g = new ArrayList[1000 + 10];
        for (int i = 0; i < g.length; ++i)
            g[i] = new ArrayList<Integer>();
        int N = 0;
        Arrays.fill(visited, false);
        for (int[] edge : edges) {
            if (!visited[edge[0]]) ++N;
            if (!visited[edge[1]]) ++N;
            visited[edge[0]] = true;
            visited[edge[1]] = true;
            if (edge[0] == edgeA[0] && edge[1] == edgeA[1]) continue;
            g[edge[0]].add(edge[1]);
            g[edge[1]].add(edge[0]);
        }
        List<Integer> q = new ArrayList<>();
        Arrays.fill(visited, false);
        int i = 0;
        q.add(1);
        visited[1] = true;
        while (i < q.size()) {
            for (int v : g[q.get(i)]) {
                if (visited[v]) continue;
                visited[v] = true;
                q.add(v);
            }
            ++i;
        }
        return q.size() == N ? edgeA : edgeB;
    }
}
