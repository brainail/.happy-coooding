package utilities.graph.struct;

/*****************************************************************************
 * A class representing a directed graph where each edge has an associated 
 * real-valued length.  Internally, the class is represented by an adjacency 
 * list.
 *****************************************************************************/
import java.util.*;

public class DirectedGraph<T>
    implements Iterable<T>
{
    /**
     * A map from nodes in the graph to sets of outgoing edges. Each set of
     * edges is represented by a map from edges to doubles.
     */
    public Map<T, Map<T, Double>> mGraph = new HashMap<T, Map<T, Double>>();

    /**
     * Default empty class constructor
     */
    public DirectedGraph()
    {
    }

    /**
     * Default class constructor to add N nodes: from 0 to (n-1)
     */
    @SuppressWarnings("unchecked")
    public DirectedGraph(int numberOfNodes)
    {
        for (Integer i = 0; i < numberOfNodes; i++) {
            addNode((T) i);
        }
    }

    /**
     * Adds a new node to the graph. If the node already exists, this function
     * is a no-op.
     * 
     * @param node The node to add.
     * @return Whether or not the node was added.
     */
    public boolean addNode(T node)
    {
        /* If the node already exists, don't do anything. */
        if (mGraph.containsKey(node)) return false;

        /* Otherwise, add the node with an empty set of outgoing edges. */
        mGraph.put(node, new HashMap<T, Double>());
        return true;
    }

    /**
     * Given a start node, destination, and length, adds an arc from the start
     * node to the destination of the length. If an arc already existed, the
     * length is updated to the specified value. If either endpoint does not
     * exist in the graph, throws a NoSuchElementException.
     * 
     * @param start The start node.
     * @param dest The destination node.
     * @param length The length of the edge.
     * @throws NoSuchElementException If either the start or destination nodes
     *             do not exist.
     */
    public void addEdge(T start, T dest, double length)
    {
        /* Confirm both endpoints exist. */
        if (!mGraph.containsKey(start) || !mGraph.containsKey(dest))
            throw new NoSuchElementException("Both nodes must be in the graph.");

        /* Add the edge. */
        mGraph.get(start).put(dest, length);
    }

    /**
     * Removes the edge from start to dest from the graph. If the edge does not
     * exist, this operation is a no-op. If either endpoint does not exist, this
     * throws a NoSuchElementException.
     * 
     * @param start The start node.
     * @param dest The destination node.
     * @throws NoSuchElementException If either node is not in the graph.
     */
    public void removeEdge(T start, T dest)
    {
        /* Confirm both endpoints exist. */
        if (!mGraph.containsKey(start) || !mGraph.containsKey(dest))
            throw new NoSuchElementException("Both nodes must be in the graph.");

        mGraph.get(start).remove(dest);
    }

    /**
     * Given a node in the graph, returns an immutable view of the edges leaving
     * that node, as a map from endpoints to costs.
     * 
     * @param node The node whose edges should be queried.
     * @return An immutable view of the edges leaving that node.
     * @throws NoSuchElementException If the node does not exist.
     */
    public Map<T, Double> edgesFrom(T node)
    {
        /* Check that the node exists. */
        Map<T, Double> arcs = mGraph.get(node);
        if (arcs == null)
            throw new NoSuchElementException("Source node does not exist.");

        return arcs;
    }

    /**
     * Returns an iterator that can traverse the nodes in the graph.
     * 
     * @return An iterator that traverses the nodes in the graph.
     */
    @Override
    public Iterator<T> iterator()
    {
        return mGraph.keySet().iterator();
    }

    /**
     * Reads in a given int[][] adjacency matrix,
     * and adds an edge node i -> j iff value in matrix == 1
     * 
     * pre: nodes are of type T; T must be of type Integer
     */
    @SuppressWarnings("unchecked")
    public void addEdges(int[][] adjacencyMatrix)
    {
        int numberOfNodes = mGraph.keySet().size();
        for (Integer i = 0; i < numberOfNodes; i++) {
            for (Integer j = 0; j < numberOfNodes; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    addEdge((T) i, (T) j, 1);
                }
            }
        }
    }

    @SuppressWarnings("unchecked")
    public int getNumberOfCompleteRows()
    {
        int numCanReach = 0, numberOfNodes = mGraph.keySet().size();
        for (Integer node = 0; node < numberOfNodes; node++) {
            // for each node - examine all its computed edges from it
            int numOutgoingPaths = 0;
            Iterator<Map.Entry<T, Double>> entries = edgesFrom((T) node)
                            .entrySet().iterator();
            while (entries.hasNext()) {
                // for each edge from this node
                Map.Entry<T, Double> entry = entries.next();
                // if node -> entry is reachable, add to count
                if (!entry.getValue().equals(Double.POSITIVE_INFINITY)) {
                    numOutgoingPaths++;
                }
            }
            if (numOutgoingPaths == numberOfNodes) {
                numCanReach++;
            }
        }
        return numCanReach;
    }

    @SuppressWarnings("unchecked")
    public int getNumberOfCompleteColumns()
    {
        int numberOfNodes = mGraph.keySet().size();
        // stores number of nodes reachable to from any other node
        // ie. column sum of #nodes = total number of nodes
        int numReachable = 0;
        for (Integer node = 0; node < numberOfNodes; node++) {
            // for each node
            int numPathsToThisNode = 0;
            for (Integer i = 0; i < numberOfNodes; i++) {
                if (!edgesFrom((T) i).get(node)
                                .equals(Double.POSITIVE_INFINITY)) {
                    numPathsToThisNode++;
                }
            }
            if (numPathsToThisNode == numberOfNodes) {
                numReachable++;
            }
        }

        return numReachable;
    }
}
