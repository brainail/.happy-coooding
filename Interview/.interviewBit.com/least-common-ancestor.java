/**
 * Definition for binary tree
 * class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public TreeNode walk(
        final TreeNode node, 
        final int val,
        final IdentityHashMap<TreeNode, Integer> marks) {
            
        if (null == node) {
            return null;
        } else if (node.val == val) {
            marks.put(node, (marks.containsKey(node) ? marks.get(node) : 0) + 1);
            return marks.get(node) > 1 ? null : node;
        }
        
        final TreeNode leftValNode = walk(node.left, val, marks);
        final TreeNode rightValNode = walk(node.right, val, marks);
        
        final TreeNode resultValNode = (null != leftValNode) 
            ? leftValNode 
            : (null != rightValNode ? rightValNode : null);
            
        if (null != resultValNode) {
            marks.put(node, (marks.containsKey(node) ? marks.get(node) : 0) + 1);
            return marks.get(node) > 1 ? null : resultValNode;
        } else {
            return null;
        }
    }
    
    public int lca(TreeNode tree, int val1, int val2) {
        final IdentityHashMap<TreeNode, Integer> marks = new IdentityHashMap<TreeNode, Integer> ();
        
        walk(tree, val1, marks);
        walk(tree, val2, marks);

        for (final Map.Entry<TreeNode, Integer> mark : marks.entrySet()) {
            if (mark.getValue() > 1) {
                return mark.getKey().val;
            }    
        }
        
        return -1; 
    }
}
