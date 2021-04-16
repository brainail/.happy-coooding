/**
 * Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
 */

class Solution {
    public List<TreeNode> generateTrees(int n) {
        return 0 == n ? Collections.emptyList() : generateTrees(1, n);
    }

    public List<TreeNode> generateTrees(int left, int right) {
        if (left > right) return Collections.singletonList((TreeNode) null);
        if (left == right) return Collections.singletonList(new TreeNode(left));
        List<TreeNode> retTrees = new ArrayList<>();
        for (int root = left; root <= right; ++root) {
            List<TreeNode> leftTrees = generateTrees(left, root - 1);
            List<TreeNode> rightTrees = generateTrees(root + 1, right);
            for (final TreeNode leftTree : leftTrees) {
                for (final TreeNode rightTree : rightTrees) {
                    final TreeNode rootNode = new TreeNode(root);
                    rootNode.left = leftTree;
                    rootNode.right = rightTree;
                    retTrees.add(rootNode);
                }
            }
        }
        return retTrees;
    }
}
