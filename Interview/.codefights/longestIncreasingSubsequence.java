int longestIncreasingSubsequence(int[] sequence) {
    final int n = sequence.length;
    int t = 0;
    final int [] tails = new int [n];
    final int [] longest = new int [n];
    int max = 0;
    for (int i = 0; i < n; ++ i) {
        final int x = sequence [i];
        int lo = 0, hi = t - 1;
        while (hi >= lo) {
            final int mi = (lo + hi) >> 1;
            if (x <= tails [mi]) hi = mi - 1; else lo = mi + 1;
        }
        tails [hi + 1] = x;
        longest [hi + 1] = (hi < 0 ? 0 : longest [hi]) + 1;
        t = Math.max(t, hi + 2);
        max = Math.max(max, longest [hi + 1]);
    }
    return max;
}
