public class Solution {
    public String countAndSay(int nth) {
        if (0 == nth) {
            return "";
        }
        
        String sSountAndSay = "1";
        while ((--nth) > 0) {
            final int length = sSountAndSay.length();
            final StringBuilder sNextCountAndSay = new StringBuilder(length * 2);
            for (int i = 0; i < length; ++ i) {
                int count = 1;
                while (i + 1 < length && sSountAndSay.charAt(i) == sSountAndSay.charAt(i + 1)) {
                    ++ count;
                    ++ i;
                }
                sNextCountAndSay.append(String.valueOf(count)).append(sSountAndSay.charAt(i));
            }
            sSountAndSay = sNextCountAndSay.toString();
        }
    
        return sSountAndSay;
    }
}
