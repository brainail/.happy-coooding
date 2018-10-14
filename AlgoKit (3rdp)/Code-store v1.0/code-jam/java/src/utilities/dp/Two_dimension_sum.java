package utilities.dp;

import java.io.*;
import java.util.*;

public class Two_dimension_sum
{
    static class Scanner
    {
        BufferedReader br;
        StringTokenizer st;

        public Scanner()
        {
            System.setOut(new PrintStream(new BufferedOutputStream(System.out),
                            true));
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next()
        {

            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    throw new RuntimeException();
                }
            }
            return st.nextToken();
        }

        public int nextInt()
        {
            return Integer.parseInt(next());
        }

        public double nextDouble()
        {
            return Double.parseDouble(next());
        }

        public String nextLine()
        {
            st = null;
            try {
                return br.readLine();
            } catch (Exception e) {
                throw new RuntimeException();
            }
        }

        public boolean endLine()
        {
            try {
                String next = br.readLine();
                while (next != null && next.trim().isEmpty())
                    next = br.readLine();
                if (next == null) return true;
                st = new StringTokenizer(next);
                return st.hasMoreTokens();
            } catch (Exception e) {
                throw new RuntimeException();
            }
        }
    }

    public static int twoDimensionSum(int[][] matriz, int alto, int ancho)
    {
        int mejor = Integer.MIN_VALUE;
        int[] actual = new int[alto];
        for (int i = 0; i < alto; i++) {
            int cuenta = 0;
            for (int j = i; j >= 0; j--) {
                cuenta += matriz[j][0];
                actual[i - j] = cuenta;
                mejor = Math.max(mejor, actual[i - j]);
            }
            for (int j = 1; j < ancho; j++) {
                cuenta = 0;
                for (int k = i; k >= 0; k--) {
                    cuenta += matriz[k][j];
                    int m = Math.max(actual[i - k] + cuenta, cuenta);
                    mejor = Math.max(mejor, m);
                    actual[i - k] = m;
                }
            }
        }
        return mejor;
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        int n = sc.nextInt();

        int[][] matriz = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matriz[i][j] = sc.nextInt();
        System.out.println(twoDimensionSum(matriz, n, n));
    }
}