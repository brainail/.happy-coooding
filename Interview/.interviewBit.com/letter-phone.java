public class Solution {
    private void genAll(
        final int pos, 
        final String digits,
        final StringBuilder buff, 
        final String [] d2c,
        final ArrayList<String> result) {
            
        if (pos == digits.length()) {
            result.add(buff.toString());
            return;
        }
        
        final int digit = (int) (digits.charAt(pos) - '0');
        for (int i = 0, size = d2c [digit].length(); i < size; ++ i) {
            buff.setCharAt(pos, d2c [digit].charAt(i));
            genAll(pos + 1, digits, buff, d2c, result);
        }
    }
    
    public ArrayList<String> letterCombinations(String digits) {
        final String [] d2c = new String [] {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        final ArrayList<String> result = new ArrayList<> ();
        final StringBuilder buff = new StringBuilder();
        buff.setLength(digits.length());
        genAll(0, digits, buff, d2c, result);
        return result;
    }
}
