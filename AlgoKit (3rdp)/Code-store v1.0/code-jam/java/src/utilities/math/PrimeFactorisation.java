package utilities.math;

import java.util.*;

public class PrimeFactorisation
{
    static boolean[] noPrimos = new boolean[20000001];

    public static void criba()
    {
        noPrimos[0] = true;
        noPrimos[1] = true;
        for (int i = 4; i < 20000001; i += 2)
            noPrimos[i] = true;
        for (int i = 3; i < 5000; i++) {
            if (!noPrimos[i]) {
                for (int j = i * i; j < 20000001; j += i)
                    noPrimos[j] = true;
            }
        }
    }

    static ArrayList<Long> primos = new ArrayList<Long>();

    public static void main(String[] args)
    {
        criba();
        for (int i = 0; i < 20000001; i++)
            if (!noPrimos[i]) primos.add((long) i);
        Scanner sc = new Scanner(System.in);
        TreeMap<Long, Long> factores = new TreeMap<Long, Long>();
        while (true) {
            long n = (long) sc.nextDouble();
            if (n == 0) return;
            long original = n;
            n <<= 2;
            n -= 3;
            factores.clear();
            while (n != 1) {
                boolean cambio = false;
                int raiz = (int) Math.sqrt(n) + 1;
                for (long i : primos) {
                    if (i > raiz) break;
                    if (n % i == 0) {
                        cambio = true;
                        if (factores.containsKey(i))
                            factores.put(i, factores.get(i) + 1);
                        else
                            factores.put(i, 1L);
                        n /= i;
                        break;
                    }
                }
                if (!cambio) {
                    if (factores.containsKey(n))
                        factores.put(n, factores.get(n) + 1);
                    else
                        factores.put(n, 1L);
                    break;
                }
            }
            int acum = 1;
            for (long i : factores.values())
                acum *= (i + 1);
            System.out.println(original + " " + acum);
        }
    }
}