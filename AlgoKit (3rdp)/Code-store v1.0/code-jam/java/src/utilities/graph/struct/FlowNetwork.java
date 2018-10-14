package utilities.graph.struct;

/*************************************************************************
 * Dependencies: Bag.java FlowEdge.java
 * 
 * A capacitated flow network, implemented using adjacency lists.
 * 
 *************************************************************************/
public class FlowNetwork
{
    private final int V;
    private int E;
    private final Bag<FlowEdge>[] adj;

    /** empty graph with V vertices */
    @SuppressWarnings("unchecked")
    public FlowNetwork(int V)
    {
        this.V = V;
        this.E = 0;
        adj = new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<FlowEdge>();
    }

    /** number of vertices and edges */
    public int V()
    {
        return V;
    }

    public int E()
    {
        return E;
    }

    /** add edge e in both v's and w's adjacency lists */
    public void addEdge(FlowEdge e)
    {
        E++;
        int v = e.from();
        int w = e.to();
        adj[v].add(e);
        adj[w].add(e);
    }

    /** return list of edges incident to v */
    public Iterable<FlowEdge> adj(int v)
    {
        return adj[v];
    }

    /** return list of all edges */
    public Iterable<FlowEdge> edges()
    {
        Bag<FlowEdge> list = new Bag<FlowEdge>();
        for (int v = 0; v < V; v++)
            for (FlowEdge e : adj(v))
                list.add(e);
        return list;
    }

    /** string representation of Graph, done in quadratic time */
    @Override
    public String toString()
    {
        String NEWLINE = System.getProperty("line.separator");
        StringBuilder s = new StringBuilder();
        s.append(V + " " + E + NEWLINE);
        for (int v = 0; v < V; v++) {
            s.append(v + ":  ");
            for (FlowEdge e : adj[v]) {
                s.append(e + "  ");
            }
            s.append(NEWLINE);
        }
        return s.toString();
    }
}
