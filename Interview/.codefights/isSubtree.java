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

boolean areSame(Tree<Integer> root1, Tree<Integer> root2) {
        if (root1 == null && root2 == null) return true;
        if (root1 == null || root2 == null) return false;
        return (root1.value.equals(root2.value) && areSame(root1.left, root2.left) && areSame(root1.right, root2.right));
    }

boolean isSubtree(Tree<Integer> S, Tree<Integer> T) {
        if (T == null) return true;
        if (S == null) return false;
        if (areSame(S, T)) return true;
        return isSubtree(S.left, T) || isSubtree(S.right, T);
}
