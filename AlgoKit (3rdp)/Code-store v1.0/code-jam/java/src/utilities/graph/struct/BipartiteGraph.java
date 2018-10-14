package utilities.graph.struct;

/*************************************************************************
 * Dependencies: Bag.java In.java StdOut.java
 * 
 * A graph, implemented using an array of sets.
 * Parallel edges and self-loops allowed.
 * 
 * The <tt>Graph</tt> class represents an undirected graph of vertices
 * named 0 through V-1.
 * It supports the following operations: add an edge to the graph,
 * iterate over all of the neighbors adjacent to a vertex.
 * Parallel edges and self-loops are permitted.
 * <p>
 */
public class BipartiteGraph
{
    private final int V;
    private int E;
    private final Bag<Integer>[] adj;

    /**
     * Create an empty graph with V vertices.
     */
    @SuppressWarnings("unchecked")
    public BipartiteGraph(int V)
    {
        if (V < 0)
            throw new RuntimeException("Number of vertices must be nonnegative");
        this.V = V;
        this.E = 0;
        adj = new Bag[V];
        for (int v = 0; v < V; v++) {
            adj[v] = new Bag<Integer>();
        }
    }

    /**
     * Create a random graph with V vertices and E edges.
     * Expected running time is proportional to V + E.
     */
    public BipartiteGraph(int V, int E)
    {
        this(V);
        if (E < 0)
            throw new RuntimeException("Number of edges must be nonnegative");
        for (int i = 0; i < E; i++) {
            int v = (int) (Math.random() * V);
            int w = (int) (Math.random() * V);
            addEdge(v, w);
        }
    }

    /**
     * Return the number of vertices in the graph.
     */
    public int V()
    {
        return V;
    }

    /**
     * Return the number of edges in the graph.
     */
    public int E()
    {
        return E;
    }

    /**
     * Add the edge v-w to graph.
     */
    public void addEdge(int v, int w)
    {
        E++;
        adj[v].add(w);
        adj[w].add(v);
    }

    /**
     * Return the list of neighbors of vertex v as in Iterable.
     */
    public Iterable<Integer> adj(int v)
    {
        return adj[v];
    }

    /**
     * Return a string representation of the graph.
     */
    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        String NEWLINE = System.getProperty("line.separator");
        s.append(V + " vertices, " + E + " edges " + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append(v + ": ");
            for (int w : adj[v]) {
                s.append(w + " ");
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }
}
