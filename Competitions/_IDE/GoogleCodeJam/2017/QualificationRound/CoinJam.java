import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

public class CoinJam {

    private static enum ExecuteMode {STD, FILE, IN_FILE};

    private FastScanner mScanner;
    private PrintWriter mWriter;

    public static void main(String [] args) {
        new CoinJam().execute(ExecuteMode.FILE);
    }

    public static final int MAXP = 65536 + 10;

    public boolean [] isPrime = new boolean [MAXP];
    public int [] bits = new int [64];
    public long [] dvs = new long [20];
    public List<Long> primes = new ArrayList<>();

    void solve() {
        int T = mScanner.nextInt();
        for (int t = 0; t < T; ++ t) {
            // long K = mScanner.nextLong();
            // mWriter.println(K);
        }

        Arrays.fill(isPrime, true);
        isPrime [0] = isPrime [1] = false;
        for (int i = 2; i < MAXP; ++ i) {
            if (! isPrime [i]) {
                continue;
            }

            primes.add((long) i);

            if ((long) i * (long) i >= MAXP) {
                continue;
            }

            for (int j = i * i; j < MAXP; j += i) {
                isPrime [j] = false;
            }
        }

        int np = primes.size();

        int N = mScanner.nextInt();
        int J = mScanner.nextInt();

        mWriter.println("Case #1:");

        int X = 0;
        bits [0] = bits [N - 1] = 1;

        while (J > 0) {
            int Y = X ++;
            for (int i = 0; i < N - 2; ++ i) {
                bits [N - i - 2] = Y % 2;
                Y /= 2;
            }

            boolean ok = true;
            for (int base = 2; base <= 10; ++ base) {
                BigInteger pw = BigInteger.ONE;
                BigInteger c = BigInteger.ZERO;

                for (int i = 0; i < N; ++ i) {
                    c = c.add(pw.multiply(BigInteger.valueOf((long) bits [N - i - 1])));
                    pw = pw.multiply(BigInteger.valueOf((long) base));
                }

                boolean hasD = false;
                for (int i = 0; i < np; ++ i) {
                    final BigInteger p = BigInteger.valueOf(primes.get(i));
                    if (p.compareTo(c) >= 0) {
                        break;
                    }

                    if (c.remainder(p).equals(BigInteger.ZERO)) {
                        hasD = true;
                        dvs [base] = primes.get(i);
                        break;
                    }
                }

                if (! hasD) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                for (int i = 0; i < N; ++ i) {
                    mWriter.print(bits [i]);
                }

                for (int base = 2; base <= 10; ++ base) {
                    mWriter.print(" ");
                    mWriter.print(dvs [base]);
                }

                mWriter.println();
                -- J;
            }
        }
    }

    void execute(final ExecuteMode executeMode) {
        try {
            mScanner = new FastScanner(executeMode);

            if (ExecuteMode.FILE != executeMode) {
                mWriter = new PrintWriter(System.out);
            } else {
                mWriter = new PrintWriter(new File("output.txt"));
            }

            solve();
        } catch (final Exception exception) {
            exception.printStackTrace();
        } finally {
            mWriter.close();
        }
    }

    class FastScanner {

        private BufferedReader mReader;
        private StringTokenizer mTokenizer;

        public FastScanner(final ExecuteMode executeMode) throws Exception {
            if (ExecuteMode.STD == executeMode) {
                mReader = new BufferedReader(new InputStreamReader(System.in));
            } else {
                mReader = new BufferedReader(new FileReader(new File("input.txt")));
            }
        }

        public FastScanner(String s) {
            try {
                mReader = new BufferedReader(new FileReader(s));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String nextToken() {
            while (null == mTokenizer || !mTokenizer.hasMoreElements()) {
                try {
                    mTokenizer = new StringTokenizer(mReader.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            return mTokenizer.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(nextToken());
        }

        long nextLong() {
            return Long.parseLong(nextToken());
        }

        double nextDouble() {
            return Double.parseDouble(nextToken());
        }

    }

}