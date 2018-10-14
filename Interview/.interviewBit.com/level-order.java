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
    private void ensureSize(final ArrayList<ArrayList<Integer>> outResult, final int n) {
        final int outN = outResult.size();
        for (int i = outN; i < n; ++ i) {
            outResult.add(new ArrayList<Integer> ());
        }
    }
    
    private void walk(
        final TreeNode node,
        final int level,
        final ArrayList<ArrayList<Integer>> outResult) {
        
        if (null == node) {
            return;
        }
        
        ensureSize(outResult, level + 1);
        outResult.get(level).add(node.val);
        
        walk(node.left, level + 1, outResult);
        walk(node.right, level + 1, outResult);
    }
    
    public ArrayList<ArrayList<Integer>> levelOrder(TreeNode node) {
        final ArrayList<ArrayList<Integer>> outResult = new ArrayList<ArrayList<Integer>> ();
        walk(node, 0, outResult);
        return outResult;
    }
}
