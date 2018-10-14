public class Solution {
    public String addBinary(String one, String two) {
        int carry = 0;
        int index = 0;
        int oneLength = one.length();
        int twoLength = two.length();
        List<Integer> result = new ArrayList<> (Math.max(oneLength, twoLength) + 1);
        while (index < oneLength || index < twoLength || carry > 0) {
            int oneDigit = index < oneLength ? (int) (one.charAt(oneLength - index - 1) - '0') : 0;
            int twoDigit = index < twoLength ? (int) (two.charAt(twoLength - index - 1) - '0') : 0;
            int rawDigit = oneDigit + twoDigit + carry;
            int digit = rawDigit % 2;
            carry = rawDigit / 2;
            result.add(digit);
            ++ index;
        }
        final StringBuilder sResult = new StringBuilder(result.size());
        for (int i = result.size() - 1; i >= 0; -- i) {
            sResult.append((char) (result.get(i) + '0'));
        }
        return sResult.toString();
    }
}
