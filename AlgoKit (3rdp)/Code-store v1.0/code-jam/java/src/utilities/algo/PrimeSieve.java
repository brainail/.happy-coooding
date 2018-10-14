package utilities.algo;

public class PrimeSieve
{
    static int[] primes = new int[446];
    static boolean[] isPrime = new boolean[3162];

    static {
        for (int i = 2; i < isPrime.length; i++)
            isPrime[i] = true;

        for (int i = 2; i * i < isPrime.length; i++)
            if (isPrime[i]) for (int j = 2 * i; j < isPrime.length; j += i)
                isPrime[j] = false;

        int p = 0;
        for (int i = 0; i < isPrime.length; i++)
            if (isPrime[i]) primes[p++] = i;
    }
}
