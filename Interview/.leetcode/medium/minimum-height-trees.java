/**
 * For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]
Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]
Note:

According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.
 */

// Linear - Collapsing 
class Solution {
    public List<Integer> findMinHeightTrees(int n, int[][] edges) {
        if (n == 1)
            return Collections.singletonList(0);

        List<Set<Integer>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; ++i)
            adj.add(new HashSet<>());
        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        List<Integer> leaves = new ArrayList<>();
        for (int i = 0; i < n; ++i)
            if (adj.get(i).size() == 1)
                leaves.add(i);

        while (n > 2) {
            n -= leaves.size();
            List<Integer> newLeaves = new ArrayList<>();
            for (int i : leaves) {
                int j = adj.get(i).iterator().next();
                adj.get(j).remove(i);
                if (adj.get(j).size() == 1)
                    newLeaves.add(j);
            }
            leaves = newLeaves;
        }
        return leaves;
    }
}


// Linear - DP
class Solution {
    int[] depth;
    List<Integer>[] graph;
    int retDepth;
    List<Integer> retRoots;

    private int calcDepth(int u, int p) {
        int maxDepth = 0;
        for (int v : graph[u])
            if (v != p)
                maxDepth = Math.max(maxDepth, calcDepth(v, u));
        return (depth[u] = maxDepth + 1);
    }

    private void findMHTs(int u, int p, int upMaxDepth) {
        int curMaxDepth = Math.max(upMaxDepth + 1, depth[u]);
        if (curMaxDepth < retDepth) {
            retDepth = curMaxDepth;
            retRoots.clear();
        }
        if (curMaxDepth == retDepth)
            retRoots.add(u);
        int maxDepthVa = -1, maxDepthVb = -1;
        for (int v : graph[u])
            if (v != p && (maxDepthVa < 0 || depth[v] > depth[maxDepthVa])) {
                maxDepthVb = maxDepthVa;
                maxDepthVa = v;
            } else if (v != p && (maxDepthVb < 0 || depth[v] > depth[maxDepthVb])) {
                maxDepthVb = v;
            }
        for (int v : graph[u]) {
            if (v == p)
                continue;
            int curUpMaxDepth = upMaxDepth + 1;
            if (maxDepthVa >= 0 && v != maxDepthVa) {
                curUpMaxDepth = Math.max(curUpMaxDepth, depth[maxDepthVa] + 1);
            }
            if (maxDepthVb >= 0 && v != maxDepthVb) {
                curUpMaxDepth = Math.max(curUpMaxDepth, depth[maxDepthVb] + 1);
            }
            findMHTs(v, u, curUpMaxDepth);
        }
    }

    public List<Integer> findMinHeightTrees(int n, int[][] edges) {
        if (0 == n)
            return Collections.emptyList();
        retRoots = new ArrayList<>();
        retDepth = Integer.MAX_VALUE;
        depth = new int[n];
        graph = new ArrayList[n];
        for (int i = 0; i < n; ++i)
            graph[i] = new ArrayList<>();
        for (int[] edge : edges) {
            graph[edge[0]].add(edge[1]);
            graph[edge[1]].add(edge[0]);
        }
        calcDepth(0, -1);
        findMHTs(0, -1, 0);
        return retRoots;
    }
}
