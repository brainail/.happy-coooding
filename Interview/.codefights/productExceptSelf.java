int productExceptSelf(int[] nums, int m) {
    final int n = nums.length;
    final int [] productLeft = new int [n];
    final int [] productRight = new int [n];
    productLeft [0] = 1;
    for (int i = 1; i < n; ++ i) {
        productLeft [i] = (int) (((long) productLeft [i - 1] * nums [i - 1]) % m);
    }
    productRight [n - 1] = 1;
    for (int i = n - 2; i >= 0; -- i) {
        productRight [i] = (int) (((long) productRight [i + 1] * nums [i + 1]) % m);
    }
    int g = 0;
    for (int i = 0; i < n; ++ i) {
        g = (int) ((g + (long) productLeft [i] * productRight [i]) % m);
    }
    return g;
}
