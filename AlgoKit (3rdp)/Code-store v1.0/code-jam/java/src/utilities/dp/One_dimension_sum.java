package utilities.dp;

import java.io.*;
import java.util.*;

public class One_dimension_sum
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

    public static int oneDimensionSum(int[] arreglo, int n)
    {
        int mejor = Integer.MIN_VALUE;
        int[] actual = new int[n];
        actual[0] = arreglo[0];
        for (int i = 1; i < n; i++) {
            actual[i] = Math.max(arreglo[i], arreglo[i] + actual[i - 1]);
            mejor = Math.max(mejor, actual[i]);
        }
        return mejor;
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        while (true) {
            int n = sc.nextInt();
            if (n == 0) return;
            int[] arreglo = new int[n];
            for (int i = 0; i < n; i++)
                arreglo[i] = sc.nextInt();
            int resultado = oneDimensionSum(arreglo, n);
            if (resultado <= 0)
                System.out.println("Losing streak.");
            else
                System.out.println("The maximum winning streak is " + resultado
                                + ".");
        }
    }
}