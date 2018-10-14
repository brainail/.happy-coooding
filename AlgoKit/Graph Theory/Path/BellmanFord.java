import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

class BellmanFordHelper {

    public static final int NULO = -1;
    public static final int INF = 1000000000;

    public static class Edge {
        public int from;
        public int to;
        public int cost;

        public Edge(final int from, final int to, final int cost) {
            this.from = from;
            this.to = to;
            this.cost = cost;
        }
    }

    public static class State {
        public int vertex;
        public int dist;

        public State(final int vertex, final int dist) {
            this.vertex = vertex;
            this.dist = dist;
        }
    }

    public int vertices;
    public int edges;

    public ArrayList<Edge> [] graph;
    public int [] dist;
    public int [] prev;
    public int lastRelaxed = NULO;
    
    public BellmanFordHelper(final int vertices, final int edges) {
        this.vertices = vertices;
        this.edges = edges;

        graph = (ArrayList<Edge> []) new ArrayList [vertices];
        dist = new int [vertices];
        prev = new int [vertices];
        for (int vertex = 0; vertex < vertices; ++ vertex) {
            graph [vertex] = new ArrayList<Edge> ();
        }
    }

    public void addEdge(final int from, final int to, final int cost) {
        graph [from].add(new Edge(from, to, cost));
    }

    public void addEdge(final int from, final int to, final int cost, final boolean isUndir) {
        addEdge(from, to, cost);
        if (isUndir) {
            addEdge(to, from, cost);
        }
    }

    public int find(final int source, final int target) {
        Arrays.fill(dist, INF);
        Arrays.fill(prev, NULO);
        
        final Queue<Integer> queue = new LinkedList<Integer> ();
        
        final int [] used = new int [vertices];
        Arrays.fill(used, NULO);

        queue.add(source);
        dist [source] = 0;
        int step = 0;

        while (!queue.isEmpty() && step < vertices) {
            ++ step;
            lastRelaxed = NULO;
            final int size = queue.size();

            for (int i = 0; i < size; ++ i) {
                final int vertex = queue.remove();

                for (final Edge edge : graph [vertex]) {
                    if (dist [vertex] + edge.cost < dist [edge.to]) {
                        dist [edge.to] = Math.max(dist [vertex] + edge.cost, -INF);
                        prev [edge.to] = vertex;
                        lastRelaxed = edge.to;
                        
                        if (step != used [edge.to]) {
                            queue.add(edge.to);
                            used [edge.to] = step;
                        }
                    }
                }
            }
        }

        return dist [target];
    }

    public boolean hasNegativeCycle() {
        return NULO != lastRelaxed;
    }

}

public class BellmanFord {

    private static enum ExecuteMode {STD, FILE, IN_FILE};

    private FastScanner mScanner;
    private PrintWriter mWriter;

    private BellmanFordHelper mBellmanFordHelper;

    public static void main(String [] args) {
        // new BellmanFord().execute(ExecuteMode.STD);
        // new BellmanFord().execute(ExecuteMode.FILE);
        new BellmanFord().execute(ExecuteMode.IN_FILE);
    }

    void solve() {
        final int vertices = mScanner.nextInt();
        final int edges = mScanner.nextInt();
        mBellmanFordHelper = new BellmanFordHelper(vertices, edges);

        for (int t = 0; t < edges; ++ t) {
            final int from = mScanner.nextInt() - 1;
            final int to = mScanner.nextInt() - 1;
            final int cost = mScanner.nextInt();
            mBellmanFordHelper.addEdge(from, to, cost, true);
        }

        final int source = mScanner.nextInt() - 1;
        final int target = mScanner.nextInt() - 1;
        final int dist = mBellmanFordHelper.find(source, target);
        
        mWriter.println("Dist: " + (BellmanFordHelper.INF != dist ? dist : "NO"));
        if (BellmanFordHelper.INF != dist && !mBellmanFordHelper.hasNegativeCycle()) {
            mWriter.print("Reverse path: ");
            int current = target;
            while (BellmanFordHelper.NULO != current) {
                mWriter.print((current + 1) + " <-- ");
                current = mBellmanFordHelper.prev [current];
            }
        } else if (mBellmanFordHelper.hasNegativeCycle()) {
            int cycleVertex = mBellmanFordHelper.lastRelaxed;
            for (int t = 0; t < vertices; ++ t) {
                cycleVertex = mBellmanFordHelper.prev [cycleVertex];
            }

            mWriter.print("Reverse cycle: ");
            int current = cycleVertex;
            boolean isEmpty = true;
            while (cycleVertex != current || isEmpty) {
                mWriter.print((current + 1) + " <-- ");
                current = mBellmanFordHelper.prev [current];
                isEmpty = false;
            }
        }
    }

    void testOne() {
        final BellmanFordHelper testBellmanFordHelper = new BellmanFordHelper(4, 6);
        testBellmanFordHelper.addEdge(0, 1, 3);
        testBellmanFordHelper.addEdge(1, 2, 5);
        testBellmanFordHelper.addEdge(0, 3, 20);
        testBellmanFordHelper.addEdge(1, 3, 15);
        testBellmanFordHelper.addEdge(2, 3, 7);
        testBellmanFordHelper.addEdge(0, 2, 12);
        final int dist = testBellmanFordHelper.find(0, 3);
        assert 15 == dist : "Wrong dist";
        assert !testBellmanFordHelper.hasNegativeCycle() : "Wrong decision about cycle";
        assert 2 == testBellmanFordHelper.prev [3] : "Wrong path";
        assert 1 == testBellmanFordHelper.prev [2] : "Wrong path";
        assert 0 == testBellmanFordHelper.prev [1] : "Wrong path";
    }

    void testTwo() {
        final BellmanFordHelper testBellmanFordHelper = new BellmanFordHelper(4, 7);
        testBellmanFordHelper.addEdge(0, 1, 3);
        testBellmanFordHelper.addEdge(1, 2, 5);
        testBellmanFordHelper.addEdge(0, 3, 20);
        testBellmanFordHelper.addEdge(1, 3, 15);
        testBellmanFordHelper.addEdge(2, 3, 7);
        testBellmanFordHelper.addEdge(0, 2, 12);
        testBellmanFordHelper.addEdge(2, 1, -13);
        final int dist = testBellmanFordHelper.find(0, 3);
        assert testBellmanFordHelper.hasNegativeCycle() : "Wrong decision about cycle";
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
            testOne();
            testTwo();
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