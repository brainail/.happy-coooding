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

class TreeLevelNode {
    final int level;
    final Tree<Integer> node;
    
    TreeLevelNode(Tree<Integer> node, int level) {
        this.node = node;
        this.level = level;
    }
}

void ensureSize(ArrayList<Integer> array, final int size) {
    while (array.size() < size) {
        array.add(Integer.MIN_VALUE);
    }
}

int[] largestValuesInTreeRows(Tree<Integer> t) {
    if (null == t) {
        return new int [0];
    }
    ArrayList<Integer> max = new ArrayList<>();
    Queue<TreeLevelNode> q = new LinkedList<TreeLevelNode>();
    q.add(new TreeLevelNode(t, 0));
    while (!q.isEmpty()) {
        final TreeLevelNode levelNode = q.remove();
        ensureSize(max, levelNode.level + 1);
        max.set(levelNode.level, Math.max(max.get(levelNode.level), levelNode.node.value));
        if (null != levelNode.node.left) {
            q.add(new TreeLevelNode(levelNode.node.left, levelNode.level + 1));
        }
        if (null != levelNode.node.right) {
            q.add(new TreeLevelNode(levelNode.node.right, levelNode.level + 1));
        }
    }
    return max.stream().mapToInt(it -> it).toArray();
}
