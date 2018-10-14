String classifyStrings(String text) {
    StringBuilder s = new StringBuilder(text);
    Set<String> vowels = new HashSet<>(Arrays.asList("a", "e", "i", "o", "u"));
    boolean mixed = false;
    for (int i = 0; i < s.length(); ++ i) {
        // v
        if (i + 2 < s.length()) {
            int v = 0, q = 0;
            for (int t = i; t <= i + 2; ++ t) {
                if ('?' != s.charAt(t)) {
                    v += vowels.contains(String.valueOf(s.charAt(t))) ? 1 : 0;
                }
                q += '?' == s.charAt(t) ? 1 : 0;
            }
            if (v == 3) return "bad";
            if (v + q == 3) {
                mixed = true;
                // make not bad for sure
                for (int t = i; t <= i + 2; ++ t) {
                    if ('?' == s.charAt(t)) {
                        s.setCharAt(t, 'z');
                        break;
                    }
                }
            }
        }
        // c
        if (i + 4 < s.length()) {
            int c = 0, q = 0;
            for (int t = i; t <= i + 4; ++ t) {
                if ('?' != s.charAt(t)) {
                    c += !vowels.contains(String.valueOf(s.charAt(t))) ? 1 : 0;
                }
                q += '?' == s.charAt(t) ? 1 : 0;
            }
            if (c == 5) return "bad";
            if (c + q == 5) {
                mixed = true;
                // make not bad for sure
                for (int t = i; t <= i + 4; ++ t) {
                    if ('?' == s.charAt(t)) {
                        s.setCharAt(t, 'o');
                        break;
                    }
                }

            }
        }
    }
    return mixed ? "mixed" : "good";
}
