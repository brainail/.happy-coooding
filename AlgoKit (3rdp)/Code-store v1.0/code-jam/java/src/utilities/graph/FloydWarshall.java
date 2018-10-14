package utilities.graph;

import utilities.graph.struct.*;

import java.util.*;

/**************************************************************************
 * An implementation of the Floyd-Warshall All-Pairs Shortest Path algorithm
 * for finding the shortest paths between all pairs of points in a directed
 * graph. The algorithm is a great example of dynamic programming. The
 * idea is to number the nodes in the graph 0, 1, ..., k, and then to
 * consider paths from one node to another that do not use any intermediary
 * node numbered higher than some value. For example, we might speak of paths
 * that never pass through an intermediary node numbered higher than 3, or
 * higher than 5, etc. As an extreme case, if we consider all paths that
 * never pass through intermediary nodes numbered higher than |V|, then we're
 * considering all possible paths (because no node is numbered |V| or higher),
 * and if we consider all paths that do not pass through nodes numbered 0 or
 * higher, then we are considering paths with no intermediary nodes at all
 * (that is, paths that are simply an edge from one node to another).
 * 
 * More formally, the algorithm is based on the following recurrence. Let
 * D(i, j, k) be the length of the shortest path from node i to node j passing
 * through no node numbered k or higher. If we have values for this function
 * for all k, then we can compute it for k + 1 as follows. There are two
 * choices. First, perhaps the shortest path from i to j not going through
 * any nodes numbered k + 1 or higher also doesn't pass through node k + 1 at
 * all. In that case, the shortest path from i to j not going through any
 * nodes numbered k + 1 or higher is just the path we already knew.
 * Alternatively, we could consider taking a path from node i to node k, again
 * not using nodes numbered k or higher (because the shortest path from i to
 * k certainly doesn't pass through k in the middle), then taking a path from
 * k to j. Formalizing the recurrence, we get that
 * 
 * D(i, j, k + 1) = min{ D(i, j, k), D(i, k, k) + D(k, j, k) }
 * 
 * As a base case, we need to compute D(i, j, 0) for all nodes i and j. This
 * is relatively straightforward. Since all paths of this form can't have
 * any intermediary nodes, we say that D(i, j, 0) is the cost of the edge from
 * i to j if such an edge exists, and is infinite otherwise (because there is
 * no direct path). Additionally, the shortest path from every node to itself
 * is also zero, since it's easy to end up where you already are!
 * 
 * Unlike Dijkstra's Algorithm, the Floyd-Warshall Algorithm has no problems
 * handling graphs with negative edge costs. Provided that the graph has no
 * negative cycles (in which case shortest paths aren't defined), the
 * algorithm will return the correct value.
 * 
 * The Floyd-Warshall algorithm works by computing the value of D using
 * dynamic programming. The shortest path from any node to another other node
 * is then given by D(i, j, |V|). The runtime of this algorithm is thus the
 * time required to compute D(i, j, |V|) for all i and j. In order to compute
 * these values, we'll need to compute D(i, j, k) for all i, j, and k. These
 * values range over the indices of the nodes, and so the runtime is O(|V|^3).
 * 
 * Notice that the above recurrence relation (for k + 1) only depends on the
 * recurrence values for k. This allows us to use the standard dynamic
 * programming optimization of just keeping around the values from the
 * previous iteration, rather than from every iteration. This gives us a
 * memory usage of O(|V|^2), although O(|V|^3) values end up getting computed.
 */
public class FloydWarshall
{
    /**
     * Given a directed, weighted graph G, runs the Floyd-Warshall algorithm on
     * that graph and produces a new graph with an edge (i, j) between each pair
     * of nodes whose cost is the cost of the shortest path from i to j in the
     * source graph.
     * 
     * @param graph The graph upon which to run the Floyd-Warshall algorithm.
     * @return A graph containing the all-pairs shortest paths of the input
     *         graph.
     */
    public static <T> DirectedGraph<T> shortestPaths(DirectedGraph<T> graph)
    {
        /* Edge case check - if the input graph is empty, we're done! */

        /*
         * Begin by getting a numbering for all of the nodes in the graph. We
         * use a Map for this because we need to be able to quickly associate
         * nodes with their indices.
         */
        Map<T, Integer> nodes = enumerateNodes(graph);

        /*
         * Create a |V| x |V| table to hold all of the D(i, j) values for the
         * current iteration.
         */
        double[][] values = new double[nodes.size()][nodes.size()];

        /*
         * Fill in the values with the base case - all distances are infinite,
         * except for nodes joined together by edges (their distances are just
         * the edge distance). We also need to record that each node is at
         * distance 0 from itself.
         * 
         * This first loop sets everything to infinity. Edges are considered in
         * the next loop.
         */
        for (int i = 0; i < nodes.size(); ++i)
            for (int j = 0; j < nodes.size(); ++j)
                values[i][j] = Double.POSITIVE_INFINITY;

        /*
         * Set distances for nodes connected by edges. Because we need to map
         * between nodes and the integers they correspond to, this loop is a bit
         * tricky. The outer loop entries are Node -> Index pairs, while the
         * inner loop entries are Node -> Distance pairs.
         */
        for (Map.Entry<T, Integer> source : nodes.entrySet()) {
            for (Map.Entry<T, Double> edge : graph.edgesFrom(source.getKey())
                            .entrySet()) {
                /*
                 * This next line is also hairy. The first part determines what
                 * indices to use when caching the edge in the table. The index
                 * of the first node is the value associated with the source
                 * node in the outer iteration. To get the index of the edge's
                 * endpoint, we have to look up the key of the edge in the node
                 * table. Finally, the length of this edge is the value in the
                 * inner entry.
                 */
                values[source.getValue()][nodes.get(edge.getKey())] = edge
                                .getValue();
            }
        }

        /*
         * Set each node to be at distance 0 from itself. We do this after
         * setting edges so that self-loops don't end up making nodes look
         * further away from themselves than need be.
         */
        for (int i = 0; i < nodes.size(); ++i)
            values[i][i] = 0.0;

        /*
         * At this point we're ready to begin the iteration. We'll start off by
         * creating a scratch array to hold the intermediary values at each
         * stage. This allows us to record the new values without losing or
         * corrupting the values from the previous iteration, which we'll be
         * modifying.
         * 
         * As an optimization, we only allocate this array once. We'll flip back
         * and forth between this buffer and the values array, much in the same
         * way that double-buffering works in graphical displays.
         */
        double[][] scratch = new double[nodes.size()][nodes.size()];
        for (int k = 0; k < nodes.size(); ++k) {
            /*
             * Scan across all (i, j) pairs computing the recurrence:
             * 
             * D(i, j, k + 1) = min{ D(i, j, k), D(i, k, k) + D(k, j, k) }
             * 
             * Part of the beauty of this algorithm is how short this code is!
             */
            for (int i = 0; i < nodes.size(); ++i)
                for (int j = 0; j < nodes.size(); ++j)
                    scratch[i][j] = Math.min(values[i][j], values[i][k]
                                    + values[k][j]);

            /*
             * Exchange the scratch work from this iteration and the actual
             * values.
             */
            double[][] temp = values;
            values = scratch;
            scratch = temp;
        }

        /*
         * We now have the shortest paths; all that's left now is converting it
         * back to a graph.
         */
        return distancesToGraph(values, nodes);
    }

    /**
     * A utility function that, given a graph, returns a Map mapping the nodes
     * in that graph to the numbers 0, 1, 2, ..., |V| - 1 in some order.
     * 
     * @param graph The graph whose nodes should be numbered.
     * @return An enumeration of the nodes in that graph.
     */
    private static <T> Map<T, Integer> enumerateNodes(DirectedGraph<T> graph)
    {
        /* Build up a HashMap so we have O(1) lookup of nodes. */
        Map<T, Integer> result = new HashMap<T, Integer>();

        /*
         * Scan across the nodes, adding them one at a time. We'll use as the
         * key in this iteration the size of the map at the time that the node
         * is added, since this is also a counter telling us the next number we
         * can use.
         */
        for (T node : graph)
            result.put(node, result.size());

        return result;
    }

    /**
     * A utility function which, given the raw result of the Floyd-Warshall
     * algorithm as an array, along with a mapping from nodes to their numbers,
     * returns a DirectedGraph encoding this information.
     * 
     * @param values The resulting values from the Floyd-Warshall algorithm.
     * @param nodeToIndex The enumeration of the nodes.
     * @return A graph encoding this information.
     */
    @SuppressWarnings("unchecked")
    private static <T> DirectedGraph<T> distancesToGraph(
        double[][] values,
        Map<T, Integer> nodeToIndex)
    {
        /*
         * In order to invert the table back to a set of values, we're going to
         * need to flip the map around to get back an association of ints to
         * nodes.
         */
        T[] indexToNode = (T[]) new Object[nodeToIndex.size()];
        for (Map.Entry<T, Integer> entry : nodeToIndex.entrySet())
            indexToNode[entry.getValue()] = entry.getKey();

        /* Create the graph to return, starting with the nodes. */
        DirectedGraph<T> result = new DirectedGraph<T>();
        for (T node : indexToNode)
            result.addNode(node);

        /*
         * Finally, add all the edges to the graph by scanning over the array
         * and converting indices into nodes.
         */
        for (int i = 0; i < nodeToIndex.size(); ++i)
            for (int j = 0; j < nodeToIndex.size(); ++j)
                result.addEdge(indexToNode[i], indexToNode[j], values[i][j]);

        return result;
    }
}
