List<Long> hashes(String s, int L, int hb) {
    List<Long> hashes = new ArrayList<>();
    int n = s.length();
    
    long [] po = new long [hb + 1];
    po [0] = 1;
    for (int i = 1; i <= hb; ++ i) po [i] = po [i - 1] * 197L;
    
    long [] ha = new long [n];
    for (int i = 0; i < n; ++ i) {
	    ha [i] = (long) (s.codePointAt(i)) * po [i];
	    if (i > 0) ha [i] += ha [i - 1];
    }
    
    // System.out.println("L = " + L + ", s = " + s);
    // System.out.println(Arrays.toString(ha));

    for (int i = 0; i + L - 1 < n; ++ i) {
        long hub = ha [i + L - 1];
        if (i > 0) hub -= ha [i - 1];    
        hub *= po [hb - i]; // balance
        hashes.add(hub);
    }
    
    // System.out.println(hashes);
    
    return hashes;
}

int longestCommonSubstring(String s, String t) {
    int hb = Math.max(s.length(), t.length());
    int lo = 1, hi = Math.min(s.length(), t.length());
    int match = 0;
    while (lo <= hi) {
        int mi = (lo + hi) >> 1;
        Set<Long> hS = new HashSet<>(hashes(s, mi, hb));
        List<Long> hT = hashes(t, mi, hb);
        boolean found = false;
        for (Long x : hT) {
            if (hS.contains(x)) {
                found = true;
                break;
            }
        }
        if (found) {
            match = mi;
            lo = mi + 1; 
        } else hi = mi - 1;
    }
    return match;
}
