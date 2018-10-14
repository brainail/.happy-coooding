/**
 * Given the head of a graph, return a deep copy (clone) of the graph. Each node
 * in the graph contains a label (int) and a list (List[UndirectedGraphNode]) of
 * its neighbors. There is an edge between the given node and each of the nodes
 * in its neighbors.
 */
public class Solution {
    IdentityHashMap<UndirectedGraphNode, UndirectedGraphNode> memo;

    private UndirectedGraphNode deepClone(UndirectedGraphNode node) {
        if (null == node)
            return null;
        if (memo.containsKey(node))
            return memo.get(node);

        UndirectedGraphNode cloneNode = new UndirectedGraphNode(node.label);
        memo.put(node, cloneNode);
        for (UndirectedGraphNode neighbor : node.neighbors) {
            cloneNode.neighbors.add(deepClone(neighbor));
        }
        return cloneNode;
    }

    public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
        memo = new IdentityHashMap<>();
        return deepClone(node);
    }
}
