/**
 * Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
 */

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
  int bestPath;

  public int maxPathSum(TreeNode root) {
    bestPath = Integer.MIN_VALUE;
    findMaxPathSum(root);
    return bestPath;
  }

  private int findMaxPathSum(TreeNode root) {
    if (null == root) return 0;
    int leftMax = findMaxPathSum(root.left);
    int rightMax = findMaxPathSum(root.right);
    bestPath = Math.max(bestPath, leftMax + rightMax + root.val);
    return Math.max(Math.max(leftMax, rightMax) + root.val, 0); 	
  }
}
