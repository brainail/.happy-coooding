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

boolean findSum(Tree<Integer> t, int s) {
    if (null == t) {
        return false;
    }
    if (null == t.left && null == t.right) {
        return t.value == s;
    } else {
        final boolean left = findSum(t.left, s - t.value);
        if (!left) {
            return findSum(t.right, s - t.value);
        } else {
            return true;
        }
    }
}

boolean hasPathWithGivenSum(Tree<Integer> t, int s) {
    return (null == t && 0 == s) || findSum(t, s);
}
