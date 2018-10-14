package utilities.games;

import java.io.*;

public class Nim
{
    static int[] factores = new int[10001];
    static boolean[] primos = new boolean[10001];

    public static void iniciarPrimos()
    {
        primos[0] = false;
        primos[1] = false;
        for (int i = 2; i <= 10000; i++)
            primos[i] = true;
        for (int i = 0; i <= 10000; i++) {
            if (primos[i]) {
                for (int j = 2 * i; j <= 10000; j += i)
                    primos[j] = false;
            }
        }
    }

    public static void sacarFactores()
    {
        iniciarPrimos();
        for (int i = 2; i <= 10000; i++) {
            int numero = i;
            int numeroFactores = 0;
            boolean cambio = true;
            if (primos[i])
                numeroFactores = 1;
            else {
                while (numero != 1 && cambio) {
                    cambio = false;
                    for (int j = 2; j <= numero; j++) {
                        if (numero % j == 0) {
                            if (primos[j]) {
                                numero /= j;
                                numeroFactores++;
                                cambio = true;
                                break;
                            }
                        }
                    }
                }
            }
            factores[i] = numeroFactores;
        }
    }

    int[][] matriz = new int[51][51];

    public static void main(String[] args)
        throws NumberFormatException,
            IOException
    {
        sacarFactores();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine());
        for (int i = 0; i < t; i++) {
            System.out.print("Case #" + (i + 1) + ": ");
            String[] pedazos = br.readLine().split(" ");
            int n = Integer.parseInt(pedazos[0]);
            int m = Integer.parseInt(pedazos[1]);
            int xor = 0;
            for (int j = 0; j < n; j++) {
                pedazos = br.readLine().split(" ");
                int sumaFila = 0;
                for (int k = 0; k < m; k++) {
                    sumaFila += factores[Integer.parseInt(pedazos[k])];
                }
                if (j == 0)
                    xor = sumaFila;
                else
                    xor = xor ^ sumaFila;
            }
            if (xor == 0)
                System.out.println("NO");
            else
                System.out.println("YES");
        }
    }

}
