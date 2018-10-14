/**
 * Definition for undirected graph.
 * class UndirectedGraphNode {
 *     int label;
 *     List<UndirectedGraphNode> neighbors;
 *     UndirectedGraphNode(int x) { label = x; neighbors = new ArrayList<UndirectedGraphNode>(); }
 * };
 */
public class Solution {
    private final IdentityHashMap<UndirectedGraphNode, UndirectedGraphNode> memo = new IdentityHashMap<> ();
    
    private UndirectedGraphNode cloneAll(final UndirectedGraphNode node) {
        if (null == node) {
            return null;
        }
        
        if (memo.containsKey(node)) {
            return memo.get(node); // early exit, memo
        }
        
        final UndirectedGraphNode cloneItem = new UndirectedGraphNode(node.label);
        memo.put(node, cloneItem);
        
        for (final UndirectedGraphNode neighborNode : node.neighbors) {
            cloneItem.neighbors.add(cloneAll(neighborNode));
        }
        
        return cloneItem;
    }
    
    public UndirectedGraphNode cloneGraph(UndirectedGraphNode node) {
        memo.clear();
        return cloneAll(node);
    }
}
