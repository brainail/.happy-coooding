package utilities.math;

import java.math.BigInteger;

public class BigIntegerSqrt
{
    public static BigInteger squareRoot(BigInteger num)
    {
        BigInteger high = num;
        BigInteger low = BigInteger.ONE;
        BigInteger two = BigInteger.valueOf(2);
        BigInteger res;
        BigInteger mid;
        do {
            mid = high.add(low).divide(two);
            if ((res = mid.multiply(mid)).compareTo(num) < 0)
                low = mid;
            else
                high = mid;
        } while (res.compareTo(num) != 0);
        return mid;
    }

    public static double squareRoot(double d)
    {
        double high = Math.ceil(d);
        double low = 0;
        double mid = 0;
        do {
            mid = (high + low) / 2;
            if (mid * mid > d)
                high = mid;
            else
                low = mid;

        } while (Math.abs(mid * mid - d) > 1e-15);
        return mid;
    }
}
