String[] composeRanges(int[] nums) {
    Long start = null;
    Long finish = null;
    List<String> ints = new ArrayList<>();
    for (final int x : nums) {
        if (null == start) {
            start = Long.valueOf(x);
            finish = Long.valueOf(x);
            continue;
        }
        if (x - finish < 2) {
            finish = Long.valueOf(x);
            continue;
        }
        if (finish - start > 0) {
            ints.add(String.format("%d->%d", start, finish));
        } else {
            ints.add(String.format("%d", start));
        }
        start = Long.valueOf(x);
        finish = Long.valueOf(x);
    }
    if (null != start && finish - start > 0) {
        ints.add(String.format("%d->%d", start, finish));
    } else if (null != start) {
        ints.add(String.format("%d", start));
    }
    return ints.toArray(new String [0]);
}
