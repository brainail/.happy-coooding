/**
 * Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
 */
class Solution {
    public int countNodes(TreeNode root) {
        if (null == root)
            return 0;
        int ret = 0;
        TreeNode node = root;
        int level = 0;
        while (node != null) {
            ret += (1 << level++);
            node = node.left;
        }
        int lo = 1 << (level - 1), hi = (1 << level) - 1;
        while (lo < hi) {
            int mi = lo + ((hi - lo + 1) >> 1);
            node = root;
            for (int b = level - 2; b >= 0 && null != node; --b) {
                if (((mi >> b) & 1) != 0)
                    node = node.right;
                else
                    node = node.left;
            }
            if (null != node)
                lo = mi;
            else
                hi = mi - 1;
        }
        ret -= (1 << level) - lo - 1;
        return ret;
    }
}

// Cut full every step
class Solution {
    public int countNodes(TreeNode root) {
        if (root == null)
            return 0;
        TreeNode left = root, right = root;
        int height = 0;
        while (right != null) {
            left = left.left;
            right = right.right;
            height++;
        }
        if (left == null)
            return (1 << height) - 1;
        return 1 + countNodes(root.left) + countNodes(root.right);
    }
}
