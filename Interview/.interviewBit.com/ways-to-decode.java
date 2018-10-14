public class Solution {
    public int numDecodings(String message) {
        if (null == message) {
            return 1;
        }
        
        final int length = message.length();
        final int [] dp = new int [length + 1];
        dp [0] = 1;
        
        for (int i = 0; i < length; ++ i) {
            if (0 == dp [i]) {
                continue; // early continue
            }
            
            if ('0' == message.charAt(i)) {
                continue;
            }
            
            dp [i + 1] += dp [i];
            if (i + 2 <= length) {
                final int number = Integer.valueOf(message.substring(i, i + 2));
                if (number <= 26) {
                    dp [i + 2] += dp [i];
                }
            }
        }
        
        return dp [length];
    }
}
