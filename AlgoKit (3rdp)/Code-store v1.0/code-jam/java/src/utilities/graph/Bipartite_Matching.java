package utilities.graph;

import java.awt.geom.*;
import java.io.*;
import java.util.*;

public class Bipartite_Matching
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

    static class Edge
    {
        int from, to, cap, flow, index;

        Edge(int fromi, int toi, int capi, int flowi, int indexi)
        {
            from = fromi;
            to = toi;
            cap = capi;
            flow = flowi;
            index = indexi;
        }
    }

    static class PushRelabel
    {
        int N;
        ArrayList<ArrayList<Edge>> G;
        long[] excess;
        int[] dist, count;
        boolean[] active;
        LinkedList<Integer> Q = new LinkedList<Integer>();

        PushRelabel(int N1)
        {
            N = N1;
            G = new ArrayList<ArrayList<Edge>>(N);
            for (int i = 0; i < N; i++)
                G.add(new ArrayList<Edge>());
            excess = new long[N];
            dist = new int[N];
            active = new boolean[N];
            count = new int[2 * N];
        }

        void AddEdge(int from, int to, int cap)
        {
            int cambio = from == to ? 1 : 0;
            G.get(from).add(
                new Edge(from, to, cap, 0, G.get(to).size() + cambio));
            G.get(to).add(new Edge(to, from, 0, 0, G.get(from).size() - 1));
        }

        void Enqueue(int v)
        {
            if (!active[v] && excess[v] > 0) {
                active[v] = true;
                Q.add(v);
            }
        }

        void Push(Edge e)
        {
            long amt = Math.min(excess[e.from], e.cap - e.flow);
            if (dist[e.from] <= dist[e.to] || amt == 0) return;
            e.flow += amt;
            G.get(e.to).get(e.index).flow -= amt;
            excess[e.to] += amt;
            excess[e.from] -= amt;
            Enqueue(e.to);
        }

        void Gap(int k)
        {
            for (int v = 0; v < N; v++) {
                if (dist[v] < k) continue;
                count[dist[v]]--;
                dist[v] = Math.max(dist[v], N + 1);
                count[dist[v]]++;
                Enqueue(v);
            }
        }

        void Relabel(int v)
        {
            count[dist[v]]--;
            dist[v] = 2 * N;
            for (Edge e : G.get(v))
                if (e.cap - e.flow > 0)
                    dist[v] = Math.min(dist[v], dist[e.to] + 1);
            count[dist[v]]++;
            Enqueue(v);
        }

        void Discharge(int v)
        {
            for (Edge e : G.get(v)) {
                if (excess[v] <= 0) break;
                Push(e);
            }
            if (excess[v] > 0) {
                if (count[dist[v]] == 1)
                    Gap(dist[v]);
                else
                    Relabel(v);
            }
        }

        long GetMaxFlow(int s, int t)
        {
            count[0] = N - 1;
            count[N] = 1;
            dist[s] = N;
            active[s] = active[t] = true;
            for (Edge e : G.get(s)) {
                excess[s] += e.cap;
                Push(e);
            }
            while (!Q.isEmpty()) {
                int v = Q.poll();
                active[v] = false;
                Discharge(v);
            }
            long totflow = 0;
            for (Edge e : G.get(s))
                totflow += e.flow;
            return totflow;
        }
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        int l = sc.nextInt();
        for (int caso = 0; caso < l; caso++) {
            if (caso != 0) System.out.println();
            int n = sc.nextInt();
            int m = sc.nextInt();
            Point2D[] ruta = new Point2D[n];
            for (int i = 0; i < n; i++)
                ruta[i] = new Point2D.Double(sc.nextInt(), sc.nextInt());
            Point2D[] interesantes = new Point2D[m];
            for (int i = 0; i < m; i++)
                interesantes[i] = new Point2D.Double(sc.nextInt(), sc.nextInt());
            PushRelabel solucion = new PushRelabel(n + m + 1);
            for (int i = 0; i < n - 1; i++) {
                Point2D inicial = ruta[i];
                Point2D ultimo = ruta[i + 1];
                double distancia = inicial.distance(ultimo);
                for (int j = 0; j < m; j++) {
                    if (2
                                    * distancia
                                    - (inicial.distance(interesantes[j]) + interesantes[j]
                                                    .distance(ultimo)) >= -1e-8)
                        solucion.AddEdge(m + i, j, 1);
                }
            }
            for (int i = 0; i < m; i++)
                solucion.AddEdge(i, n + m, 1);
            for (int i = 0; i < n; i++)
                solucion.AddEdge(n + m - 1, m + i, 1);
            int res = (int) solucion.GetMaxFlow(n + m - 1, n + m);
            System.out.println(n + res);
            System.out.print(((int) ruta[0].getX()) + " "
                            + ((int) ruta[0].getY()));
            for (int i = 1; i < n; i++) {
                ArrayList<Edge> actuales = solucion.G.get(m + (i - 1));
                for (Edge e : actuales) {
                    if (e.flow == 1) {
                        System.out.print(" "
                                        + ((int) interesantes[e.to].getX())
                                        + " "
                                        + ((int) interesantes[e.to].getY()));
                        break;
                    }
                }
                System.out.print(" " + ((int) ruta[i].getX()) + " "
                                + ((int) ruta[i].getY()));
            }
            System.out.println();
        }
    }
}