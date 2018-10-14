private static final int MODULO = (int) 1e9 + 7;

int mapDecoding(String message) {
    final int n = message.length();
    final int [] dp = new int [n + 1];
    dp [0] = 1;
    
    for (int pos = 0; pos < n; ++ pos) {
        if (0 == dp [pos]) continue;
        for (int codeIndex = 1; codeIndex <= 26; ++ codeIndex) {
            final String code = String.valueOf(codeIndex);
            final int nCode = code.length();
            
            boolean match = true;
            for (int t = 0; t < nCode; ++ t) {
                if (pos + t >= n || message.charAt(pos + t) != code.charAt(t)) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                dp [pos + nCode] = dp [pos + nCode] + dp [pos];
                if (dp [pos + nCode] >= MODULO) dp [pos + nCode] -= MODULO;
            }
        }
    }
    
    return dp [n];
}
