String sortByString(String s, String t) {
    final int [] count = new int [26];
    for (int i = t.length() - 1; i >= 0; -- i) {
        count [t.charAt(i) - 'a'] = i;
    }
    System.out.println(Arrays.toString(count));
    final char [] result = s.toCharArray();
    for (int i = 0; i < result.length; ++ i)
        for (int q = i + 1; q < result.length; ++ q)
            if (count [result [q] - 'a'] < count [result [i] - 'a']) {
                char tmp = result [i];
                result [i] = result [q];
                result [q] = tmp;
            }
    return new String(result);
}
