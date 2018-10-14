int[] nearestGreater(int[] a) {
    final int n = a.length;
    final int [] next = new int [n];
    Arrays.fill(next, -1);
    final int [] prev = new int [n];
    Arrays.fill(prev, -1);
    final Stack<Integer> nextStack = new Stack<>();
    for (int i = 0; i < n; ++ i) {
        while (!nextStack.empty() && a [i] > a [nextStack.peek()]) {
            if (next [nextStack.peek()] < 0) next [nextStack.peek()] = i;
            nextStack.pop();
        }
        nextStack.push(i);
    }
    final Stack<Integer> prevStack = new Stack<>();
    for (int i = n - 1; i >= 0; -- i) {
        while (!prevStack.empty() && a [i] > a [prevStack.peek()]) {
            if (prev [prevStack.peek()] < 0) prev [prevStack.peek()] = i;
            prevStack.pop();
        }
        prevStack.push(i);
    }
    final int [] nearest = new int [n];
    Arrays.fill(nearest, -1);
    for (int i = 0; i < n; ++ i) {
        if (next [i] < 0 && prev [i] < 0) continue;
        if (next [i] < 0) {
            nearest [i] = prev [i];
            continue;
        }
        if (prev [i] < 0) {
            nearest [i] = next [i];
            continue;
        }
        nearest [i] = Math.abs(prev [i] - i) <= Math.abs(next [i] - i)
            ? prev [i] 
            : next [i];
    }
    return nearest;
}
