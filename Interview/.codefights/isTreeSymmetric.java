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

boolean isSymmetric(Tree<Integer> l, Tree<Integer> r) {
    if (null == l && null == r) return true;
    if (null == l || null == r || !l.value.equals(r.value)) return false;
    return isSymmetric(l.left, r.right) && isSymmetric(l.right, r.left);
}

boolean isTreeSymmetric(Tree<Integer> t) {
    if (null == t) return true;
    return isSymmetric(t.left, t.right);
}
