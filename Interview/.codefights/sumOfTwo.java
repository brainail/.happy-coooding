boolean sumOfTwo(int[] a, int[] b, int v) {
    final Set<Integer> set = new HashSet<Integer>(a.length);
    for (final int x: a) set.add(x);
    for (final int x: b) {
        if (set.contains(v - x)) return true;
    }
    return false;
}
