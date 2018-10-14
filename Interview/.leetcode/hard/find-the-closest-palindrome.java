/**
 * Given an integer n, find the closest integer (not including itself), which is
 * a palindrome.
 * 
 * The 'closest' is defined as absolute difference minimized between two
 * integers.
 * 
 * Example 1: Input: "123" Output: "121"
 */
class Solution {
    public StringBuilder copyHalf(StringBuilder p) {
        int len = p.length();
        for (int i = 0; i < len / 2; ++i) {
            p.setCharAt(len - i - 1, p.charAt(i));
        }
        return p;
    }

    public StringBuilder appendHalf(StringBuilder p, boolean includeTail) {
        int len = p.length();
        if (!includeTail) {
            len -= len & 1;
        }
        for (int i = len - 1; i >= 0; --i) {
            p.append(p.charAt(i));
        }
        return p;
    }

    public long toNumber(StringBuilder p, int len) {
        long number = 0;
        for (int i = 0; i < len; ++i) {
            number = number * 10 + (int) (p.charAt(i) - '0');
        }
        return number;
    }

    public String nearestPalindromic(String s) {
        long original = Long.valueOf(s);

        List<Long> numbers = new ArrayList<>();
        StringBuilder p = new StringBuilder(s);
        numbers.add(toNumber(copyHalf(p), p.length()));

        long half = toNumber(p, (p.length() + 1) / 2);

        StringBuilder loP = appendHalf(new StringBuilder(String.valueOf(half - 1)), false);
        numbers.add(toNumber(loP, loP.length()));
        loP = appendHalf(new StringBuilder(String.valueOf(half - 1)), true);
        numbers.add(toNumber(loP, loP.length()));

        StringBuilder hiP = appendHalf(new StringBuilder(String.valueOf(half + 1)), false);
        numbers.add(toNumber(hiP, hiP.length()));
        hiP = appendHalf(new StringBuilder(String.valueOf(half + 1)), true);
        numbers.add(toNumber(hiP, hiP.length()));

        StringBuilder loMagic = new StringBuilder();
        for (int i = 0; i < s.length() - 1; ++i) {
            loMagic.append('9');
        }
        numbers.add(toNumber(loMagic, loMagic.length()));

        StringBuilder hiMagic = new StringBuilder("1");
        for (int i = 0; i < s.length() - 1; ++i) {
            hiMagic.append('0');
        }
        hiMagic.append('1');
        numbers.add(toNumber(hiMagic, hiMagic.length()));

        Collections.sort(numbers);
        System.out.println(numbers);

        long result = -1;
        for (Long x : numbers) {
            if (x == original)
                continue;
            if (result < 0 || Math.abs(result - original) > Math.abs(x - original)) {
                result = x;
            }
        }

        return String.valueOf(result);
    }
}

/*
long ans = 0, diff = Long.MAX_VALUE, n = 0;

private void update(String val) {
    try {
        long tmp = Long.parseLong(val);
        if (tmp == n) return;
        if (Math.abs(tmp - n) < diff || (Math.abs(tmp - n) == diff && tmp < ans)) {
            ans = tmp;
            diff = Math.abs(tmp - n);
        }
    } catch (Exception e) { }
}

private void concat(long leftHalf) {
    String s = "" + leftHalf, rs = new StringBuilder(s).reverse().toString();
    update(s + rs); // abc -> abccba
    update(s + rs.substring(1)); // abc -> abcba
}

public String nearestPalindromic(String n) {
    this.n = Long.parseLong(n);
    diff = Long.MAX_VALUE;
    long leftHalf = Long.parseLong(n.substring(0, (n.length() + 1) / 2));
    concat(leftHalf - 1);
    concat((leftHalf - 1) * 10 + 9); // Handle 1, 1000, 100000, etc.
    concat(leftHalf);
    concat(leftHalf + 1);
    concat((leftHalf + 1) / 10); // Handle 9, 999, 99999, etc.
    return "" + ans;
}
 */