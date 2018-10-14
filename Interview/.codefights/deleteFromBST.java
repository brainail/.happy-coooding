/**
 * A tree is considered a binary search tree (BST) if for each of its nodes the following is true:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and the right subtrees must also be binary search trees.
Removing a value x from a BST t is done in the following way:

If there is no x in t, nothing happens;
Otherwise, let t' be a subtree of t such that t'.value = x.
If t' has a left subtree, remove the rightmost node from it and put it at the root of t';
Otherwise, remove the root of t' and its right subtree becomes the new t's root.
For example, removing 4 from the following tree has no effect because there is no such value in the tree:

    5
   / \
  2   6
 / \   \
1   3   8
       /
      7
Removing 5 causes 3 (the rightmost node in left subtree) to move to the root:

    3
   / \
  2   6
 /     \
1       8
       /
      7
And removing 6 after that creates the following tree:

    3
   / \
  2   8
 /   /
1   7
You're given a binary search tree t and an array of numbers queries. Your task is to remove queries[0], queries[1], etc., from t, step by step, following the algorithm above. Return the resulting BST.
 */

//
// Definition for binary tree:
// class Tree<T> {
//   Tree(T x) {
//     value = x;
//   }
//   T value;
//   Tree<T> left;
//   Tree<T> right;
// }
// 

private Tree<Integer> removeNode(Tree<Integer> cur, int data) {
    if (cur == null) {
        // skip
    } else if (data < cur.value) {            
        cur.left = removeNode(cur.left, data); // find in left
    } else if (data > cur.value){
        cur.right = removeNode(cur.right, data); // find in right
    } else {  
        // #1 approach
        // if (cur.left == null && cur.right == null) {
        //     cur = null; // no leafs, just remove
        // } else if (cur.right == null) {
        //     cur = cur.left; // only left, just remove as middleman 
        // } else if (cur.left == null) {
        //     cur = cur.right; // only right, just remove as middleman 
        // } else { // both, find replacement, remove replacement 
        //     final Tree<Integer> replacement = findRightmost(cur.left);
        //     cur.value = replacement.value;
        //     cur.left = removeNode(cur.left, replacement.value);
        // }
        
        // #2 approach
        if (cur.left != null) {
            final Tree<Integer> replacement = findRightmost(cur.left);
            cur.value = replacement.value;
            cur.left = removeRightmost(cur.left);
        } else {
            cur = cur.right;
        }
    }
    return cur;
}

private Tree<Integer> removeRightmost(Tree<Integer> node) {
    if (null == node.right) {
        return node.left;
    } else {
        node.right = removeRightmost(node.right);
    }
    return node;
}

private Tree<Integer> findRightmost(Tree<Integer> node) {
    while (node != null && node.right != null) node = node.right; 
    return node;
}

Tree<Integer> deleteFromBST(Tree<Integer> tree, int[] queries) {
    for (int i = 0; i < queries.length; ++ i) {
        tree = removeNode(tree, queries [i]);
    }
    return tree;
}
