int[] nextLarger(int[] a) {
    final int n = a.length;
    final int [] next = new int [n];
    Arrays.fill(next, -1);
    final Stack<Integer> stack = new Stack<>();
    for (int i = 0; i < n; ++ i) {
        while (!stack.empty() && a [i] >= a [stack.peek()]) {
            if (next [stack.peek()] < 0) {
                next [stack.peek()] = a [i];
            }
            stack.pop();
        }
        stack.push(i);
    }
    return next;
}
