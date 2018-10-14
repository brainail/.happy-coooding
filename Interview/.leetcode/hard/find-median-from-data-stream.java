/**
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * 
 * For example, [2,3,4], the median is 3
 * 
 * [2,3], the median is (2 + 3) / 2 = 2.5
 * 
 * Design a data structure that supports the following two operations:
 * 
 * void addNum(int num) - Add a integer number from the data stream to the data
 * structure. double findMedian() - Return the median of all elements so far.
 * 
 * 
 * Example:
 * 
 * addNum(1) addNum(2) findMedian() -> 1.5 addNum(3) findMedian() -> 2
 */
class MedianFinder {
    private static class Node {
        public Node left;
        public Node right;
        public int value;
        public int size;
        public int count;

        public Node(int value) {
            this.value = value;
            this.size = 1;
            this.count = 1;
        }

        int leftSize() {
            return null != left ? left.size : 0;
        }

        int rightSize() {
            return null != right ? right.size : 0;
        }
    }

    private Node tree;

    public MedianFinder() {
        // do nothing
    }

    private void addNode(int value, Node prev, Node node) {
        if (null == node) {
            Node newNode = new Node(value);
            if (value < prev.value)
                prev.left = newNode;
            else
                prev.right = newNode;
        } else if (node.value == value) {
            ++node.size;
            ++node.count;
        } else {
            if (value < node.value)
                addNode(value, node, node.left);
            if (value > node.value)
                addNode(value, node, node.right);
            node.size = node.leftSize() + node.rightSize() + node.count;
        }
    }

    public void addNum(int num) {
        if (null == tree) {
            tree = new Node(num);
        } else {
            addNode(num, null, tree);
        }
    }

    private int findMedian(Node node, int k) {
        if (k <= node.leftSize()) {
            return findMedian(node.left, k);
        } else if (k <= node.leftSize() + node.count) {
            return node.value;
        } else {
            return findMedian(node.right, k - node.leftSize() - node.count);
        }
    }

    public double findMedian() {
        if (null == tree)
            return 0;
        double median = (double) findMedian(tree, (tree.size + 1) / 2);
        if ((tree.size % 2) == 0) {
            double median2 = (double) findMedian(tree, (tree.size + 2) / 2);
            median = (median + median2) / 2;
        }
        return median;
    }
}
