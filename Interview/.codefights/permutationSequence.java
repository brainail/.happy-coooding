String permutationSequence(int n, long k) {
    long [] fa = new long [16];
    fa [0] = 1;
    for (int i = 1; i < 16; ++ i) fa [i] = fa [i - 1] * i;
    StringBuilder perm = new StringBuilder(n);
    boolean [] used = new boolean [n];
    for (int i = 0; i < n; ++ i) {
        int fel = 0;
        for (int el = 0; el < n; ++ el)
            if (!used [el]) {
                int hi = Math.min(n - i - 1, fa.length - 1);
                if (k - fa [hi] <= 0) {
                    fel = el;
                    break;
                }
                k -= fa [hi];
            }
        used [fel] = true;
        perm.append(String.valueOf(fel + 1));
    }
    return perm.toString();
}
