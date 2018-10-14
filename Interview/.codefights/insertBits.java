int insertBits(int n, int a, int b, int k) {
    for (int i = a; i <= b; ++ i) {
        if (((n >> i) & 1) > 0) { 
            n ^= 1 << i; // remove
        }
        if (((k >> (i - a)) & 1) > 0) {
            n ^= 1 << i; // set
        }
    }
    return n;
    // return n & ~((1 << (b - a + 1)) - 1 << a) | k << a; // smart way
}
