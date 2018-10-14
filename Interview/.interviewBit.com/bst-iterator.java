/**
 * Definition for binary tree
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */

public class Solution {
    
    final Stack<TreeNode> iteratorPath = new Stack<TreeNode> ();

    private static void populateIterator(final TreeNode fromNode, final Stack<TreeNode> iteratorPath) {
        TreeNode node = fromNode;
        while (null != node) {
            iteratorPath.push(node);
            node = node.left;
        }
    }

    public Solution(TreeNode root) {
        iteratorPath.clear();
        populateIterator(root, iteratorPath);
    }

    /** @return whether we have a next smallest number */
    public boolean hasNext() {
        return !iteratorPath.empty();
    }

    /** @return the next smallest number */
    public int next() {
        final TreeNode nextNode = iteratorPath.pop();
        final int nextValue = nextNode.val;
        populateIterator(nextNode.right, iteratorPath);
        return nextValue;
    }
    
}

/**
 * Your Solution will be called like this:
 * Solution i = new Solution(root);
 * while (i.hasNext()) System.out.print(i.next());
 */
