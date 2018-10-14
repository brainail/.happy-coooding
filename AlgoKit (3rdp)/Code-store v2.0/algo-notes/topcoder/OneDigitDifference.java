public class OneDigitDifference {
    public int getSmallest(int N) {
        if (N == 0) return 1;

        int limit = 1; // should start from 1

        while (N / limit >= 10) limit *= 10;

        return N % limit;
    }
}

