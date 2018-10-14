package utilities.string;

import java.io.*;
import java.util.*;

public class Aho_Corasick
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
                return !st.hasMoreTokens();
            } catch (Exception e) {
                throw new RuntimeException();
            }
        }
    }

    static class Nodo
    {
        Nodo siguiente;
        int valor;

        public Nodo(int v)
        {
            valor = v;
        }
    }

    static class PMA
    {
        PMA next[];
        PMA fail;
        Nodo accept;
        Nodo ultimo;

        PMA()
        {
            next = new PMA[27];
        }

        void add(int n)
        {
            if (accept == null)
                accept = ultimo = new Nodo(n);
            else {
                ultimo.siguiente = new Nodo(n);
                ultimo = ultimo.siguiente;
            }
        }

        void addAll(PMA other)
        {
            if (other.accept == null) return;
            if (accept == null) {
                accept = other.accept;
                ultimo = other.ultimo;
            } else {
                ultimo.siguiente = other.accept;
                ultimo = other.ultimo;
            }
        }

        void match(char t[], int inicio, int tam, int dp[], int nuevo)
        {
            int n = inicio + tam;
            PMA v = this;
            for (int i = inicio; i < n; i++) {
                int c = t[i] - 'a';
                while (v.next[c] == null)
                    v = v.fail;
                v = v.next[c];
                Nodo actual = v.accept;
                while (actual != null) {
                    dp[actual.valor] = Math.max(dp[actual.valor], nuevo);
                    actual = actual.siguiente;
                }
            }
        }
    }

    static PMA buildPMA(char p[][], int size)
    {
        PMA root = new PMA();
        for (int i = 0; i < size; i++) {
            PMA t = root;
            for (int j = 0; j < p[i].length; j++) {
                int c = p[i][j] - 'a';
                if (t.next[c] == null) t.next[c] = new PMA();
                t = t.next[c];
            }
            t.add(i);
        }
        for (int c = 0; c <= 25; c++)
            if (root.next[c] == null) root.next[c] = root;
        Queue<PMA> Q = new ArrayDeque<PMA>();
        for (int c = 0; c <= 25; c++) {
            if (root.next[c] != root) {
                root.next[c].fail = root;
                Q.add(root.next[c]);
            }
        }
        while (!Q.isEmpty()) {
            PMA t = Q.poll();
            for (int c = 0; c <= 25; c++) {
                if (t.next[c] != null) {
                    Q.add(t.next[c]);
                    PMA r = t.fail;
                    while (r.next[c] == null)
                        r = r.fail;
                    t.next[c].fail = r.next[c];
                    t.next[c].addAll(r.next[c]);
                }
            }
        }
        return root;
    }

    static int kmp(char t[], char p[], int fail[])
    {
        int n = t.length;
        int m = p.length;
        for (int i = 0, k = 0; i < n; i++) {
            while (k >= 0 && p[k] != t[i])
                k = fail[k];
            if (++k >= m) return 1;
        }
        return 0;
    }

    static int[] buildFail(char p[])
    {
        int m = p.length;
        int fail[] = new int[m + 1];
        int j = fail[0] = -1;
        for (int i = 1; i <= m; i++) {
            while (j >= 0 && p[j] != p[i - 1])
                j = fail[j];
            fail[i] = ++j;
        }
        return fail;
    }

    public static void main(String[] args)
        throws FileNotFoundException
    {
        int[] dp = new int[10100];
        Scanner sc = new Scanner();
        String[] palabrasS = new String[10100];
        char[][] palabras = new char[10100][];
        while (true) {
            int n = sc.nextInt();
            if (n == 0) break;
            for (int i = 0; i < n; i++) {
                palabrasS[i] = sc.next();
                dp[i] = 1;
            }
            Arrays.sort(palabrasS, 0, n, new Comparator<String>() {
                @Override
                public int compare(String o1, String o2)
                {
                    return o2.length() - o1.length();
                }
            });
            for (int i = 0; i < n; i++)
                palabras[i] = palabrasS[i].toCharArray();
            PMA raiz = buildPMA(palabras, n);
            int mejor = 0;
            for (int i = 0; i < n; i++) {
                int dpSig = dp[i] + 1;
                raiz.match(palabras[i], 1, palabras[i].length - 1, dp, dpSig);
                raiz.match(palabras[i], 0, palabras[i].length - 1, dp, dpSig);
                mejor = Math.max(mejor, dp[i]);
            }
            System.out.println(mejor);
            if (n > 100) System.gc();
        }
    }
}