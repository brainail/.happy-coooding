package utilities.algo;

public class ModularExponentiation
{
    public static long pow(long x, long c, long n)
    {
        long z = 1;
        // 64 bits in a long.
        for (int i = 63; i >= 0; i--) {
            z = z * z % n;
            if ((c & (1L << i)) != 0) z = z * x % n;
        }
        return z;
    }

}
