package utilities.graph;

import java.util.*;

import utilities.graph.struct.*;

/*************************************************************************
 * Dependencies: Graph.java
 * 
 * Given a graph, find either (i) a bipartition or (ii) an odd-length cycle.
 * Runs in O(E + V) time.
 * 
 *************************************************************************/
public class BipartiteChecker
{
    private boolean isBipartite; // is the graph bipartite?
    private final boolean[] color; // color[v] gives vertices on one side of
                                   // bipartition
    private final boolean[] marked; // marked[v] = true if v has been visited in
                                    // DFS
    private final int[] edgeTo; // edgeTo[v] = last edge on path to v
    private Stack<Integer> cycle; // odd-length cycle

    public BipartiteChecker(BipartiteGraph G)
    {
        isBipartite = true;
        color = new boolean[G.V()];
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];

        for (int v = 0; v < G.V(); v++) {
            if (!marked[v]) {
                dfs(G, v);
            }
        }
        assert check(G);
    }

    private void dfs(BipartiteGraph G, int v)
    {
        marked[v] = true;
        for (int w : G.adj(v)) {

            // short circuit if odd-length cycle found
            if (cycle != null) return;

            // found uncolored vertex, so recur
            if (!marked[w]) {
                edgeTo[w] = v;
                color[w] = !color[v];
                dfs(G, w);
            }

            // if v-w create an odd-length cycle, find it
            else if (color[w] == color[v]) {
                isBipartite = false;
                cycle = new Stack<Integer>();
                cycle.push(w); // don't need this unless you want to include
                               // start vertex twice
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
            }
        }
    }

    boolean isBipartite()
    {
        return isBipartite;
    }

    boolean color(int v)
    {
        return color[v];
    }

    public Iterable<Integer> cycle()
    {
        return cycle;
    }

    private boolean check(BipartiteGraph G)
    {
        // graph is bipartite
        if (isBipartite) {
            for (int v = 0; v < G.V(); v++) {
                for (int w : G.adj(v)) {
                    if (color[v] == color[w]) {
                        System.err.printf(
                            "edge %d-%d with %d and %d in same side of bipartition\n",
                            v, w, v, w);
                        return false;
                    }
                }
            }
        }

        // graph has an odd-length cycle
        else {
            // verify cycle
            int first = -1, last = -1;
            for (int v : cycle()) {
                if (first == -1) first = v;
                last = v;
            }
            if (first != last) {
                System.err.printf("cycle begins with %d and ends with %d\n",
                    first, last);
                return false;
            }
        }

        return true;
    }
}
