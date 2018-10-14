int findFirstSubstringOccurrence(String x, String s) {
    int [] p = new int [s.length()];
    for (int i = 1, prefix = 0; i < s.length(); ++ i) {
        while (prefix > 0 && s.charAt(i) != s.charAt(prefix)) {
            prefix = p [prefix - 1];
        }
        if (s.charAt(i) == s.charAt(prefix)) {
            ++ prefix;
        }
        p [i] = prefix;
    }
    for (int i = 0, prefix = 0; i < x.length(); ++ i) {
        while (prefix > 0 && x.charAt(i) != s.charAt(prefix)) {
            prefix = p [prefix - 1];
        }
        if (x.charAt(i) == s.charAt(prefix)) {
            ++ prefix;
        }
        if (prefix == s.length()) {
            return i - prefix + 1;
        }
    }
    return -1;
}
