void gen(int pos, String s, StringBuilder comb, boolean [] used, Set<String> set) {
    if (pos == s.length()) {
        set.add(comb.toString());
        return;
    }
    
    for (int i = 0; i < s.length(); ++ i) 
        if (!used [i]) {
            comb.setCharAt(pos, s.charAt(i));
            used [i] = true;
            gen(pos + 1, s, comb, used, set);
            used [i] = false;
        }
}

String[] stringPermutations(String s) {
    if (s.isEmpty()) return new String [0];
    TreeSet<String> set = new TreeSet<>();
    boolean [] used = new boolean [s.length()];
    StringBuilder comb = new StringBuilder();
    comb.setLength(s.length());
    gen(0, s, comb, used, set);
    String [] result = new String [set.size()];
    int index = 0;
    for (String x : set) {
        result [index ++] = x;
    }
    return result;
}
