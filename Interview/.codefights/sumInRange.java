int sumInRange(int[] nums, int[][] queries) {
    final int MODULO = (int) 1e9 + 7;
    for (int i = 1; i < nums.length; ++ i) {
        nums [i] += nums [i - 1];
        nums [i] = (nums [i] + MODULO) % MODULO;
    }
    int sum = 0;
    for (final int [] query : queries) {
        int interval = nums [query [1]] 
            - (query [0] > 0 ? nums [query [0] - 1] : 0);
        interval = (interval + MODULO) % MODULO;
        sum = (sum + interval) % MODULO;
    }
    return sum;
}
