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


int[] traverseTree(Tree<Integer> t) {
    if (null == t) {
        return new int [0];
    }
    ArrayList<Integer> traverse = new ArrayList<>();
    Queue<Tree<Integer>> q = new LinkedList<Tree<Integer>>();
    q.add(t);
    while (!q.isEmpty()) {
        final Tree<Integer> node = q.remove();
        traverse.add(node.value);
        if (null != node.left) {
            q.add(node.left);
        }
        if (null != node.right) {
            q.add(node.right);
        }
    }
    return traverse.stream().mapToInt(i -> i).toArray();
}
