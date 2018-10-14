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

int kthSmallestInBST(Tree<Integer> t, int k) {
    int[] K = new int[] {0};
    helper(t, k, K);
    return K[0];
}

private int helper(Tree<Integer> t, int k, int[] K) {
    if (t == null) return 0;
    int left = helper(t.left, k, K);
    if (left + 1 == k) K[0] = t.value;
    int right = helper(t.right, k - left - 1, K);
    return left + right + 1;
}

/**
 * Global
 * 
 * int k, r;

int kthSmallestInBST(Tree<Integer> t, int k) {
    this.k = k;
    f(t);
    return r;
}

void f(Tree<Integer> t) {
    if (t.left != null) f(t.left);
    --k;
    if (k == 0) r = t.value;
    if (t.right != null) f(t.right);
}
 */
