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
    private boolean checkBST(final TreeNode node, final int fromVal, final int toVal) {
        if (null == node) {
            return true;
        }
        
        if (node.val < fromVal || node.val > toVal) {
            return false;
        }
        
        return (checkBST(node.left, fromVal, node.val - 1) && checkBST(node.right, node.val + 1, toVal));
    }
    
    public int isValidBST(TreeNode tree) {
        return checkBST(tree, Integer.MIN_VALUE, Integer.MAX_VALUE) ? 1 : 0;
    }
}
