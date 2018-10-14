import java.io.*;
import java.lang.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;
import java.util.*;

public class P45_FightingTheZombie {

    private static enum ExecuteMode {STD, FILE, IN_FILE};

    private FastScanner mScanner;
    private PrintWriter mWriter;

    public static void main(String [] args) {
        // new P45_FightingTheZombie().execute(ExecuteMode.STD);
        new P45_FightingTheZombie().execute(ExecuteMode.FILE);
        // new P45_FightingTheZombie().execute(ExecuteMode.IN_FILE);
    }

    void solve() {
        final int T = mScanner.nextInt();
        for (int t = 0; t < T; ++ t) {
            final int H = mScanner.nextInt();
            final int S = mScanner.nextInt();

            double maxProbability = 0d;
            for (int s = 0; s < S; ++ s) {
                final String spell = mScanner.nextToken()
                        .replace(" ", "")
                        .replace("d", " ")
                        .replace("+", " ")
                        .replace("-", " -");
                final String [] commands = spell.split(" ");

                final int X = Integer.parseInt(commands [0]);
                final int Y = Integer.parseInt(commands [1]);
                final int Z = commands.length > 2 ? Integer.parseInt(commands [2]) : 0;

                final double probability = calcProbability(H, X, Y, Z);
                maxProbability = Math.max(maxProbability, probability);
            }

            mWriter.printf(Locale.US, "Case #%d: %.7f\n", t + 1, maxProbability);
        }
    }

    private static final BigInteger [][] dp = new BigInteger [22][444];

    private double calcProbability(final int H, final int X, final int Y, final int Z) {
        final BigInteger numberOfAllOutcomes = BigInteger.valueOf(Y).pow(X);

        final int maxSum = X * Y;
        for (int i = 0; i <= X; ++ i) {
            for (int j = 0; j <= maxSum; ++ j) {
                dp [i][j] = BigInteger.ZERO;
            }
        }

        dp [0][0] = BigInteger.ONE;
        for (int i = 0; i < X; ++ i) {
            for (int j = 0; j <= i * Y; ++ j) {
                if (dp [i][j].equals(BigInteger.ZERO)) {
                    continue; // early skip
                }

                for (int tryY = 1; tryY <= Y; ++ tryY) {
                    dp [i + 1][j + tryY] = dp [i + 1][j + tryY].add(dp [i][j]);
                }
            }
        }

        BigInteger suitableOutcomes = BigInteger.ZERO;
        for (int j = 1; j <= X * Y; ++ j)
            if (j + Z >= H) {
                suitableOutcomes = suitableOutcomes.add(dp [X][j]);
            }

        final BigDecimal good = new BigDecimal(suitableOutcomes);
        final BigDecimal all = new BigDecimal(numberOfAllOutcomes);
        final BigDecimal probability = good.divide(all, 10, RoundingMode.HALF_UP);

        final double rtvProbability = probability.doubleValue();
        return rtvProbability;
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