boolean containsDuplicates(int [] nums) {
    final Set<Integer> set = new HashSet<>(nums.length);
    for (final int x: nums) {
        if (set.contains(x)) return true;
        set.add(x);
    }
    return false;
}
