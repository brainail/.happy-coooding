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
    private int findMaxDepth(final TreeNode node) {
        if (null == node) {
            return -1000000000;
        }
        if (null == node.left && null == node.right) {
            return 1;
        }
        
        return Math.max(findMaxDepth(node.left), findMaxDepth(node.right)) + 1;
    }
    
    public int maxDepth(TreeNode tree) {
        return findMaxDepth(tree);
    }
}
