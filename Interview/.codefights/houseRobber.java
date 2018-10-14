int houseRobber(int[] nums) {
    final int n = nums.length;
    final int [] dp = new int [n];
    Arrays.fill(dp, 0);
    for (int house = 0; house < n; ++ house) {
        // take
        final int beforeTake = house > 1 ? dp [house - 2] : 0;
        dp [house] = Math.max(dp [house], beforeTake + nums [house]);
        // skip
        final int beforeSkip = house > 0 ? dp [house - 1] : 0;
        dp [house] = Math.max(dp [house], beforeSkip);
    }
    return n > 0 ? dp [n - 1] : 0;
}
