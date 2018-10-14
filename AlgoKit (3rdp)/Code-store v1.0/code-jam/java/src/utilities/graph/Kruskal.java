package utilities.graph;

import static java.util.Arrays.*;
import static java.lang.Math.*;

import java.io.*;
import java.util.*;

class Main
{
    public static void main(String[] args)
        throws IOException
    {
        new Main().run();
    }

    // Data structures for Kruskal's algorithm
    private double[] xs, ys;
    private Vector<HashSet<Integer>> vertexGroups;
    private TreeSet<Edge> kruskalEdges;

    private void run()
        throws IOException
    {
        int MODE = 0;
        Scanner sc = null;
        PrintWriter pw = null;
        switch (MODE) {
        case 0:
            sc = new Scanner(System.in);
            pw = new PrintWriter(System.out);
            break;
        case 1:
            sc = new Scanner(new FileReader("/Users/lwy08/Downloads/input"));
            pw = new PrintWriter(System.out);
            break;
        case 2:
            sc = new Scanner(new FileReader("A-small.in"));
            pw = new PrintWriter(new FileWriter("A-small.out"));
            break;
        case 3:
            sc = new Scanner(new FileReader("A-large.in"));
            pw = new PrintWriter(new FileWriter("A-large.out"));
            break;
        }

        int _nc = sc.nextInt();
        for (int _c = 1; _c <= _nc; _c++) {
            sc.nextLine();
            int N = sc.nextInt();

            xs = new double[N];
            ys = new double[N];
            for (int i = 0; i < N; i++) {
                xs[i] = sc.nextDouble();
                ys[i] = sc.nextDouble();
                // System.out.println(xs[i] + " " + ys[i]);
            }

            TreeSet<Edge> edges = new TreeSet<Edge>();
            for (int i = 0; i < xs.length; i++) {
                for (int j = 0; j < ys.length; j++) {
                    if (i < j) {
                        edges.add(new Edge(i, j, xs, ys));
                    }
                }
            }
            vertexGroups = new Vector<HashSet<Integer>>();
            kruskalEdges = new TreeSet<Edge>();
            for (Edge edge : edges) {
                insertEdge(edge);
            }
            double total = 0;
            for (Edge edge : kruskalEdges) {
                // System.err.println(edge);
                total += edge.weight;
            }

            pw.println(String.format("%.2f", total));

            if (_c < _nc) {
                pw.println();
            }

            // pw.println(String.format("Case #%d: %.2f", _c, total));
        }

        pw.close();
        sc.close();
    }

    // Helper method
    private HashSet<Integer> getVertexGroup(Integer vertex)
    {
        for (HashSet<Integer> vertexGroup : vertexGroups) {
            if (vertexGroup.contains(vertex)) {
                return vertexGroup;
            }
        }
        return null;
    }

    // Core of algorithm
    private void insertEdge(Edge edge)
    {
        HashSet<Integer> vertexGroupA = getVertexGroup(edge.i);
        HashSet<Integer> vertexGroupB = getVertexGroup(edge.j);
        if (vertexGroupA == null) {
            kruskalEdges.add(edge);
            if (vertexGroupB == null) {
                HashSet<Integer> htNewVertexGroup = new HashSet<Integer>();
                htNewVertexGroup.add(edge.i);
                htNewVertexGroup.add(edge.j);
                vertexGroups.add(htNewVertexGroup);
            } else {
                vertexGroupB.add(edge.i);
            }
        } else {
            if (vertexGroupB == null) {
                vertexGroupA.add(edge.j);
                kruskalEdges.add(edge);
            } else if (vertexGroupA != vertexGroupB) {
                vertexGroupA.addAll(vertexGroupB);
                vertexGroups.remove(vertexGroupB);
                kruskalEdges.add(edge);
            } else {
                // do nothing
            }
        }
    }
}

class Edge
    implements Comparable<Edge>
{
    int i, j;
    double[] xs, ys;
    double weight;

    public Edge(int i, int j, double[] xs, double[] ys)
    {
        double x1 = xs[i];
        double x2 = xs[j];
        double y1 = ys[i];
        double y2 = ys[j];
        this.i = i;
        this.j = j;
        this.xs = xs;
        this.ys = ys;
        weight = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    @Override
    public int compareTo(Edge e)
    {
        // == is not compared so that duplicate values are not eliminated.
        return weight < e.weight ? -1 : 1;
    }

    @Override
    public String toString()
    {
        return String.format("(%.1f,%.1f) -> (%.1f,%.1f)", xs[i], ys[i], xs[j],
            ys[j]);
    }
}
