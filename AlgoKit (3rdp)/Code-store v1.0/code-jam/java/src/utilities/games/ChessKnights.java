package utilities.games;

import java.io.*;
import java.util.*;

public class ChessKnights
{
    static class Scanner
    {
        BufferedReader br;
        StringTokenizer st;

        public Scanner()
        {
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
    }

    static final int RNG = 100;
    static final int ZERO = 50;

    static int[][] dir = new int[][] { { -2, -1 }, { -2, 1 }, { -1, -2 },
                    { -1, 2 }, { 1, -2 }, { 1, 2 }, { 2, -1 }, { 2, 1 } };

    static int[][] d = new int[RNG][RNG];
    static int[][] q = new int[RNG * RNG][2];
    static int tail;

    static void add(int r1, int c1, int d1)
    {
        try {
            if (d[r1][c1] == -1) {
                d[r1][c1] = d1;
                q[tail][0] = r1;
                q[tail++][1] = c1;
            }
        } catch (Exception e) {

        }
    }

    static long moo(long x, long y)
    {
        x = Math.abs(x);
        y = Math.abs(y);
        if (x < y) {
            long temp = x;
            x = y;
            y = temp;
        }
        if (x < 20 && y < 20) return d[(int) (ZERO + x)][(int) (ZERO + y)];
        if (y == 0) {
            long k = Math.max(0, (x - 10) / 4);
            return k * 2 + moo(x - k * 4, 0);
        } else if (x < y + 3) {
            long k = Math.max(0, (y - 10) / 3);
            return k * 2 + moo(x - k * 3, y - k * 3);
        } else {
            long k = Math.min(Math.min(x - y, y), Math.max(x / 2, y) - 5);
            return k + moo(x - k * 2, y - k);
        }
    }

    static long mejor(long x0, long y0, long x1, long y1)
    {
        x1 -= x0;
        y1 -= y0;
        return moo(x1, y1);
    }

    static long[][] dp = new long[1 << 15][15];
    static long[][] distancias = new long[15][15];

    static long dp(int libres, int caballoActual)
    {
        if (libres == 0) return 0;
        if (dp[libres][caballoActual] != -1) return dp[libres][caballoActual];
        int temp = libres;
        long mejor = Long.MAX_VALUE;
        for (int i = 0; i < 15; i++) {
            if ((temp & 1) == 1)
                mejor = Math.min(
                    mejor,
                    distancias[caballoActual][i]
                                    + dp(libres ^ (1 << i), caballoActual + 1));
            temp >>>= 1;
        }
        return dp[libres][caballoActual] = mejor;
    }

    public static void main(String[] args)
        throws FileNotFoundException
    {
        for (int i = 0; i < RNG; ++i)
            for (int j = 0; j < RNG; ++j)
                d[i][j] = -1;
        tail = 0;
        add(ZERO, ZERO, 0);
        for (int i = 0; i < tail; ++i)
            for (int j = 0; j < 8; ++j)
                add(q[i][0] + dir[j][0], q[i][1] + dir[j][1],
                    d[q[i][0]][q[i][1]] + 1);
        Scanner sc = new Scanner();
        int caso = 1;
        while (true) {
            int n = sc.nextInt();
            if (n == 0) return;
            int[][] caballos = new int[n][2];
            int[][] destinos = new int[n][2];
            for (int i = 0; i < n; i++) {
                caballos[i][0] = sc.nextInt();
                caballos[i][1] = sc.nextInt();
            }
            for (int i = 0; i < n; i++) {
                destinos[i][0] = sc.nextInt();
                destinos[i][1] = sc.nextInt();
            }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    distancias[i][j] = mejor(caballos[i][0], caballos[i][1],
                        destinos[j][0], destinos[j][1]);
            for (int i = 0; i < 1 << 15; i++)
                for (int j = 0; j < 15; j++)
                    dp[i][j] = -1;
            System.out.println(caso++ + ". " + dp((1 << n) - 1, 0));
        }

    }

}
