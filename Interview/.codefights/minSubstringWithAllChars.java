String minSubstringWithAllChars(String s, String t) {
    if (t.isEmpty()) return "";
    
    final int [] reqCount = new int [26];
    for (int index = 0; index < t.length(); ++ index) {
        ++ reqCount [t.charAt(index) - 'a'];
    }
    
    final int [] curCount = new int [26];
    int right = -1;
    int leftReq = t.length();
    
    int resultLeft = -1;
    int resultLength = Integer.MAX_VALUE;
    
    for (int left = 0; left < s.length(); ++ left) {
        if (right < left) {
            right = left;
            int ch = s.charAt(left) - 'a';
            curCount [ch] = 1;
            if (curCount [ch] == reqCount [ch]) -- leftReq;
        }
        
        while (right + 1 < s.length() && leftReq > 0) {
            int ch = s.charAt(right + 1) - 'a';
            // if (curCount [ch] + 1 > reqCount [ch] && reqCount [ch] > 0) break;
            ++ curCount [ch];
            ++ right;
            if (curCount [ch] == reqCount [ch]) -- leftReq;
        }
        
        if (leftReq == 0) {
            if (right - left + 1 < resultLength) {
                resultLeft = left;
                resultLength = right - left + 1;
            }
        }
        
        int ch = s.charAt(left) - 'a';
        if (curCount [ch] == reqCount [ch]) ++ leftReq;
        -- curCount [ch];        
    }
    
    return s.substring(resultLeft, resultLeft + resultLength);
}
