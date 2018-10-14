/**
 * Note: Your solution should have O(inorder.length) time complexity, since this is what you will be asked to accomplish in an interview.

Let's define inorder and preorder traversals of a binary tree as follows:

Inorder traversal first visits the left subtree, then the root, then its right subtree;
Preorder traversal first visits the root, then its left subtree, then its right subtree.
For example, if tree looks like this:

    1
   / \
  2   3
 /   / \
4   5   6
then the traversals will be as follows:

Inorder traversal: [4, 2, 1, 5, 3, 6]
Preorder traversal: [1, 2, 4, 3, 5, 6]
Given the inorder and preorder traversals of a binary tree t, but not t itself, restore t and return it.
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

Tree<Integer> restoreTree(
    final int [] inorder, final int inLeft, final int inRight,
    final int [] preorder, final int preLeft, final int preRight) {
    
    if (inLeft > inRight || preLeft > preRight) return null; // enough
    final Tree<Integer> current = new Tree<>(preorder [preLeft]);
    final int index = findIndex(preorder [preLeft], inorder, inLeft, inRight); // 0..
    current.left = restoreTree(inorder, inLeft, inLeft + index - 1, preorder, preLeft + 1, preLeft + index);
    current.right = restoreTree(inorder, inLeft + index + 1, inRight, preorder, preLeft + index + 1, preRight);
    return current;
}

private int findIndex(final int value, final int [] values, final int left, final int right) { // it's possible to be faster
    for (int index = 0; index < right - left + 1; ++ index) {
        if (values [left + index] == value) return index;
    }
    return Integer.MIN_VALUE; // never please
}

Tree<Integer> restoreBinaryTree(int[] inorder, int[] preorder) {
    return restoreTree(inorder, 0, inorder.length - 1, preorder, 0, preorder.length - 1);
}

/**
 * Stack
 * 
 * Tree<Integer> restoreBinaryTree(int[] inorder, int[] preorder) {
    Stack<Tree<Integer>> stack = new Stack<>();
    
    int inorderIndex = 0;
    int preorderIndex = 0;
    
    Tree<Integer> root = new Tree<>(preorder[preorderIndex]);
    preorderIndex++;
    stack.push(root);
    
    while(!stack.isEmpty()) {
        Tree<Integer> top = stack.peek();
        if (top.value.intValue() == inorder[inorderIndex]) {
            stack.pop();
            inorderIndex++;
            
            if(inorderIndex == inorder.length) break;
            if(!stack.isEmpty() && stack.peek().value.intValue() == inorder[inorderIndex]) continue;
            
            Tree<Integer> node = new Tree<>(preorder[preorderIndex]);
            top.right = node;
            preorderIndex++;
            stack.push(node);
        } else {
            Tree<Integer> node = new Tree<>(preorder[preorderIndex]);
            preorderIndex++;
            top.left = node;
            stack.push(node);
        }
    }
    
    return root;
}
 */
