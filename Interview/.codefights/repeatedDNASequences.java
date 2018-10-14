String[] repeatedDNASequences(String s) {
    List<String> result = new ArrayList<>();
    TreeMap<String, Integer> dict = new TreeMap<>();
    for (int i = 0; i + 9 < s.length(); ++ i) {
        final String part = s.substring(i, i + 10);
        Integer count = dict.get(part);
        if (null == count) {
            count = 0;
        }
        dict.put(part, count + 1);
    }
    for (Map.Entry<String, Integer> entry : dict.entrySet()) {
        if (entry.getValue() > 1) {
            result.add(entry.getKey());
        }
    }
    return result.toArray(new String [0]);
}
