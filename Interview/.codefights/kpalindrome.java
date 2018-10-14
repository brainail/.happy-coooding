boolean kpalindrome(String s, int k) {
    int n = s.length();
    int [][] kp = new int [n][n];
    for (int i = 0; i < n; ++ i) {
        Arrays.fill(kp [i], Integer.MAX_VALUE);
        kp [i][i] = 0;
        if (i + 1 < n) {
            kp [i][i + 1] = s.charAt(i) == s.charAt(i + 1) ? 0 : 1;
        }
    }
    for (int len = 3; len <= n; ++ len) {
        for (int st = 0; st <= n - len; ++ st) {
            int fi = st + len - 1;
            kp [st][fi] = Math.min(kp [st][fi], kp [st + 1][fi] + 1);
            kp [st][fi] = Math.min(kp [st][fi], kp [st][fi - 1] + 1);
            if (s.charAt(st) == s.charAt(fi)) {
                kp [st][fi] = Math.min(kp [st][fi], kp [st + 1][fi - 1]);
            }
        }
    }
    return kp [0][n - 1] <= k;
}
