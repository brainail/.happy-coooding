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

int findSums(final Tree<Integer> node, final Map<Integer, Integer> sumCount) {
    if (null == node) {
        return 0;
    }
    
    final int leftSum = findSums(node.left, sumCount);
    final int rightSum = findSums(node.right, sumCount);
    final int nodeSum = leftSum + rightSum + node.value;
    sumCount.put(nodeSum, sumCount.containsKey(nodeSum) 
            ? sumCount.get(nodeSum) + 1 : 1);
    return nodeSum;
}

int[] mostFrequentSum(Tree<Integer> t) {
    final Map<Integer, Integer> sumCount = new HashMap<>();
    findSums(t, sumCount);
    int maxCount = 0;
    final ArrayList<Integer> sums = new ArrayList<>();
    for (Map.Entry<Integer, Integer> sum : sumCount.entrySet()) {
        if (sum.getValue() > maxCount) {
            sums.clear();
            sums.add(sum.getKey());
            maxCount = sum.getValue();
        } else if (sum.getValue() == maxCount) {
            sums.add(sum.getKey());
        }
    }
    return sums.stream().sorted().mapToInt(it -> it).toArray();
}
