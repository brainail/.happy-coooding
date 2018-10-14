public class FixedDiceGameDiv2 {
    public double getExpectation(int a, int b) {
        if (a <= b) {
            return ((double)(a + 1)) * 2.0 / 3.0;
        } else {
            double up = (b * b * b - b) * 2.0 / 3.0 + (a + b + 1) * (a - b) * b;
            double lower = b * (b - 1) + 2 * (a - b) * b;
            return up / lower;
        }
    }
}
