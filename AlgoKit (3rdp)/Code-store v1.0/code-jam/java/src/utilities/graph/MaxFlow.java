package utilities.graph;

import java.io.*;
import java.util.*;

public class MaxFlow
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

    static class Vuelo
        implements Comparable<Vuelo>
    {
        int origen;
        int destino;
        int cap;
        int salida;
        int llegada;
        int entradaN;
        int salidaN;

        public Vuelo(int origen, int destino, int cap, int salida, int llegada,
                     int entradaN, int salidaN)
        {
            this.origen = origen;
            this.destino = destino;
            this.cap = cap;
            this.salida = salida;
            this.llegada = llegada;
            this.entradaN = entradaN;
            this.salidaN = salidaN;
        }

        @Override
        public int compareTo(Vuelo o)
        {
            return salida - o.salida;
        }
    }

    static int actual;
    static HashMap<String, Integer> ciudades = new HashMap<String, Integer>();

    public static int darCiudad(String s)
    {
        if (ciudades.containsKey(s)) return ciudades.get(s);
        ciudades.put(s, actual);
        return actual++;
    }

    private static int convertirHora(int hora)
    {
        return ((hora / 100) * 60) + (hora % 100);
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        while (true) {
            actual = 0;
            ciudades.clear();
            int nCiudades = sc.nextInt();
            int origen = darCiudad(sc.next());
            int destino = darCiudad(sc.next());
            int ultimaLlegada = convertirHora(sc.nextInt());
            int nVuelos = sc.nextInt();
            int nAct = 1;
            ArrayList<Vuelo> vuelos = new ArrayList<Vuelo>(nVuelos);
            ArrayList<ArrayList<Vuelo>> porCiudad = new ArrayList<ArrayList<Vuelo>>(
                            nCiudades + 1);
            for (int i = 0; i < nCiudades + 1; i++)
                porCiudad.add(new ArrayList<Vuelo>());
            for (int i = 0; i < nVuelos; i++) {
                int a = darCiudad(sc.next());
                int b = darCiudad(sc.next());
                int cap = sc.nextInt();
                int s = convertirHora(sc.nextInt());
                int l = convertirHora(sc.nextInt());
                Vuelo nuevo = new Vuelo(a, b, cap, s, l, nAct++, nAct++);
                vuelos.add(nuevo);
                porCiudad.get(a).add(nuevo);
            }
            nAct++;
            PushRelabel solucion = new PushRelabel(nAct);
            for (int i = 0; i < nCiudades + 1; i++) {
                ArrayList<Vuelo> actual = porCiudad.get(i);
                Collections.sort(actual);
                for (int j = 0; j < actual.size() - 1; j++)
                    solucion.AddEdge(actual.get(j).entradaN,
                        actual.get(j + 1).entradaN, 2000000000);
            }
            for (Vuelo a : vuelos) {
                for (Vuelo b : porCiudad.get(a.destino)) {
                    if (a.llegada + 30 <= b.salida) {
                        solucion.AddEdge(a.salidaN, b.entradaN, a.cap);
                        break;
                    }
                }
                solucion.AddEdge(a.entradaN, a.salidaN, a.cap);
                if (a.origen == origen) solucion.AddEdge(0, a.entradaN, a.cap);
                if (a.destino == destino && a.llegada <= ultimaLlegada)
                    solucion.AddEdge(a.salidaN, nAct - 1, a.cap);
            }
            System.out.println(solucion.GetMaxFlow(0, nAct - 1));
            if (sc.endLine()) return;
        }
    }
}