public class Solution {
    public int gcd(int a, int b) {
        return b > 0 ? gcd(b, a % b) : a;
    }
}
