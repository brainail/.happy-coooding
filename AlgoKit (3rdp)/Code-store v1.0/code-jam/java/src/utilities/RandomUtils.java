package utilities;

import static java.lang.Math.*;
import static utilities.Constants.*;

public class RandomUtils
{
    public static int[] xrange(int start, int end)
    {
        return xrange(start, end, 1);
    }

    public static int[] xrange(int start, int end, int step)
    {
        assert ((end - start) % step == 0) : "xrange(): Invalid arguments";
        int numElements = (end - start) / step + 1;
        int[] result = new int[numElements];
        for (int i = 0; i < numElements; i++) {
            result[i] = start + i * step;
        }
        return result;
    }

    public static int[] nextInts(int size, int low, int high)
    {
        int[] result = new int[size];
        for (int i = 0; i < result.length; i++) {
            result[i] = nextInt(low, high);
        }
        return result;
    }

    public static int nextInt(int low, int high)
    {
        // rng.nextInt(n) fails when n = 0 (cause n must be positive)
        if (low == high) {
            return low;
        }
        return rng.nextInt(abs(low - high)) + (low < high ? low : high);
    }
}
