import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

class DijkstraHelper {

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

    PriorityQueue<State> queue;
    
    public DijkstraHelper(final int vertices, final int edges) {
        this.vertices = vertices;
        this.edges = edges;

        graph = (ArrayList<Edge> []) new ArrayList [vertices];
        dist = new int [vertices];
        prev = new int [vertices];
        for (int vertex = 0; vertex < vertices; ++ vertex) {
            graph [vertex] = new ArrayList<Edge> ();
        }

        queue = new PriorityQueue<State>(vertices, new Comparator<State>() {
            public int compare(final State sA, State sB) {
                return sA.dist - sB.dist;
            }
        });
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
        dist [source] = 0;
        queue.clear();
        queue.add(new State(source, 0));
        while (!queue.isEmpty()) {
            final State state = queue.remove();
            if (state.dist > dist [state.vertex]) continue;
            for (final Edge edge : graph [state.vertex]) {
                if (dist [state.vertex] + edge.cost < dist [edge.to]) {
                    dist [edge.to] = dist [state.vertex] + edge.cost;
                    prev [edge.to] = state.vertex;
                    queue.add(new State(edge.to, dist [edge.to]));
                }
            }
        }
        return dist [target];
    }

}

public class Dijkstra {

    private static enum ExecuteMode {STD, FILE, IN_FILE};

    private FastScanner mScanner;
    private PrintWriter mWriter;

    private DijkstraHelper mDijkstraHelper;

    public static void main(String [] args) {
        // new Dijkstra().execute(ExecuteMode.STD);
        // new Dijkstra().execute(ExecuteMode.FILE);
        new Dijkstra().execute(ExecuteMode.IN_FILE);
    }

    void solve() {
        final int vertices = mScanner.nextInt();
        final int edges = mScanner.nextInt();
        mDijkstraHelper = new DijkstraHelper(vertices, edges);

        for (int t = 0; t < edges; ++ t) {
            final int from = mScanner.nextInt() - 1;
            final int to = mScanner.nextInt() - 1;
            final int cost = mScanner.nextInt();
            mDijkstraHelper.addEdge(from, to, cost, true);
        }

        final int source = mScanner.nextInt() - 1;
        final int target = mScanner.nextInt() - 1;
        final int dist = mDijkstraHelper.find(source, target);
        
        mWriter.println("Dist: " + (DijkstraHelper.INF != dist ? dist : "NO"));
        if (DijkstraHelper.INF != dist) {
            mWriter.print("Reverse path: ");
            int current = target;
            while (DijkstraHelper.NULO != current) {
                mWriter.print((current + 1) + " <-- ");
                current = mDijkstraHelper.prev [current];
            }
        }
    }

    void testOne() {
        final DijkstraHelper testDijkstraHelper = new DijkstraHelper(4, 6);
        testDijkstraHelper.addEdge(0, 1, 3);
        testDijkstraHelper.addEdge(1, 2, 5);
        testDijkstraHelper.addEdge(0, 3, 20);
        testDijkstraHelper.addEdge(1, 3, 15);
        testDijkstraHelper.addEdge(2, 3, 7);
        testDijkstraHelper.addEdge(0, 2, 12);
        final int dist = testDijkstraHelper.find(0, 3);
        assert 15 == dist : "Wrong dist";
        assert 2 == testDijkstraHelper.prev [3] : "Wrong path";
        assert 1 == testDijkstraHelper.prev [2] : "Wrong path";
        assert 0 == testDijkstraHelper.prev [1] : "Wrong path";
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