public class Solution {
    public String reverseWords(String str) {
        final int length = str.length();
        final List<String> words = new ArrayList<> (length / 2);
        int i = 0;
        
        while (i < length) {
            if (str.charAt(i) == ' ') {
                ++ i;
                continue;
            }
            
            int q = i;
            while (q < length && str.charAt(q) != ' ') {
                ++ q;
            }
            
            words.add(str.substring(i, q));
            i = q + 1;
        }
        
        final StringBuilder sBuilder = new StringBuilder(length / 2);
        for (int t = words.size() - 1; t >= 0; -- t) {
            sBuilder.append(words.get(t));
            if (t > 0) {
                sBuilder.append(' ');
            }
        }
        
        return sBuilder.toString();
    }
}
