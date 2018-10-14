int primesSum2(int n) {
    boolean [] composite = new boolean [n + 1];
    int sum = 0;
    for (int i = 2; i <= n; ++ i)
        if (!composite [i]) {
            sum = (sum + i) % 1000000007;
            if (i * (long) i > n) continue;
            for (int t = i * i; t <= n; t += i) {
                composite [t] = true;
            }
        }
    return sum;
}
