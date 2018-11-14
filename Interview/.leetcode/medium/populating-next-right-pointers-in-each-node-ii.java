/**
 * Given a binary tree

struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.
Example:

Given the following binary tree,

     1
   /  \
  2    3
 / \    \
4   5    7
After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL
 */

// optimal (use next from previous level)
public class Solution {
    public void connect(TreeLinkNode root) {
        TreeLinkNode head = null, prev = null, cur = root;
        while (cur != null) {
            while (cur != null) { 
                if (cur.left != null) {
                    if (prev != null) {
                        prev.next = cur.left;
                    } else {
                        head = cur.left;
                    }
                    prev = cur.left;
                }
                if (cur.right != null) {
                    if (prev != null) {
                        prev.next = cur.right;
                    } else {
                        head = cur.right;
                    }
                    prev = cur.right;
                }
                cur = cur.next;
            }
            cur = head;
            head = null;
            prev = null;
        }
    }
}

 // #que
public class Solution {
    public void connect(TreeLinkNode root) {
        if (null == root)
            return;
        Deque<TreeLinkNode> que = new ArrayDeque<>();
        que.offer(root);
        int countOnLevel = 1;
        while (!que.isEmpty()) {
            TreeLinkNode prev = null;
            int size = countOnLevel;
            countOnLevel = 0;
            for (int i = 0; i < size; ++i) {
                TreeLinkNode cur = que.poll();
                if (null != prev)
                    prev.next = cur;
                if (null != cur.left) {
                    ++countOnLevel;
                    que.offer(cur.left);
                }
                if (null != cur.right) {
                    ++countOnLevel;
                    que.offer(cur.right);
                }
                prev = cur;
            }
        }
    }
}
