package utilities.algo;

import java.util.*;

public class WeightedGraph
{
    List<HashMap<Integer, Integer>> adjacencyMap = new ArrayList<HashMap<Integer, Integer>>();

    public WeightedGraph(int vertices)
    {
        for (int i = 0; i < vertices; i++)
            adjacencyMap.add(new HashMap<Integer, Integer>());
    }

    public WeightedGraph(WeightedGraph g)
    {
        for (int i = 0; i < g.vertexCount(); i++)
            adjacencyMap.add(new HashMap<Integer, Integer>(g.adjacencyMap
                            .get(i)));
    }

    public Set<Integer> getNeighbors(int v)
    {
        return adjacencyMap.get(v).keySet();
    }

    public int getEdgeWeight(int u, int v)
    {
        return adjacencyMap.get(u).get(v);
    }

    public void setEdgeWeight(int u, int v, int weight)
    {
        addDirectedEdge(u, v, weight);
    }

    public int vertexCount()
    {
        return adjacencyMap.size();
    }

    public boolean existsEdge(int u, int v)
    {
        return adjacencyMap.get(u).containsKey(v);
    }

    public void addDirectedEdge(int u, int v, int weight)
    {
        adjacencyMap.get(u).put(v, weight);
    }

    public void addUndirectedEdge(int u, int v, int weight)
    {
        addDirectedEdge(u, v, weight);
        addDirectedEdge(v, u, weight);
    }

    @Override
    public String toString()
    {
        String s = "";
        for (int i = 0; i < adjacencyMap.size(); i++) {
            s += i + ": \n";
            s += "\t" + adjacencyMap.get(i) + "\n";
        }
        return s;
    }
}
