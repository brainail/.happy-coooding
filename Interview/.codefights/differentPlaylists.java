long pow(long x, int n) {
    long res = 1;
    while (n > 0) {
        if ((n & 1L) > 0) res = (res * x) % 1000000007;
        n >>= 1L;
        x = (x * x) % 1000000007;
    }
    return res;
}

int differentPlaylists(int n, int k, int l) {
    long res = 1;
    for (int i = 0; i < Math.min(l, k); ++ i) {
        if (n - i <= 0) break;
        res = (res * (n - i)) % 1000000007;
    }
    if (n - k > 0) {
        res = (res * pow(n - k, l - k)) % 1000000007;
    } else {
        if (l - k > 0) res = 0;
    }
    return (int) res;
}
