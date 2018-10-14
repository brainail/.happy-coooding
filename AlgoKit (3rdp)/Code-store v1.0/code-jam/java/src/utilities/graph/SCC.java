package utilities.graph;

import java.io.*;
import java.util.*;

public class SCC
{
    static class Node
        implements Comparable<Node>
    {
        final int name;
        ArrayList<Node> adjacents = new ArrayList<Node>(100);
        boolean visited = false;
        int lowlink = -1;
        int index = -1;

        public Node(final int argName)
        {
            name = argName;
        }

        @Override
        public int compareTo(final Node argNode)
        {
            return argNode == this ? 0 : -1;
        }
    }

    static int index = 0;
    static ArrayDeque<Node> stack = new ArrayDeque<Node>();
    static ArrayList<ArrayList<Node>> SCC = new ArrayList<ArrayList<Node>>();

    public static ArrayList<ArrayList<Node>> SCC(Node[] nodes, int size)
    {
        index = 0;
        SCC.clear();
        stack.clear();
        for (int i = 0; i < size; i++)
            if (nodes[i].index == -1) tarjan(nodes[i]);
        return SCC;
    }

    public static void tarjan(Node v)
    {
        v.index = index;
        v.lowlink = index;
        index++;
        stack.push(v);
        for (Node n : v.adjacents) {
            if (n.index == -1) {
                tarjan(n);
                v.lowlink = Math.min(v.lowlink, n.lowlink);
            } else if (stack.contains(n))
                v.lowlink = Math.min(v.lowlink, n.index);
        }
        if (v.lowlink == v.index) {
            Node n;
            ArrayList<Node> component = new ArrayList<Node>();
            do {
                n = stack.pop();
                component.add(n);
            } while (n != v);
            SCC.add(component);
        }
    }

    static Node[] nodes = new Node[2000];
    static TreeSet<Integer> inComponent = new TreeSet<Integer>();
    static boolean[][][] visited = new boolean[1000][1000][4];

    public static void main(String[] args)
        throws FileNotFoundException
    {
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < 2000; i++)
            nodes[i] = new Node(i);
        while (sc.hasNextInt()) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < 4; k++)
                        visited[i][j][k] = false;

            int dn = n << 1;
            for (int i = 0; i < dn; i++) {
                nodes[i].adjacents.clear();
                nodes[i].visited = false;
                nodes[i].lowlink = -1;
                nodes[i].index = -1;
            }
            for (int i = 0; i < m; i++) {
                String a = sc.next();
                char as = a.charAt(0);
                a = a.substring(1);
                String b = sc.next();
                char bs = b.charAt(0);
                b = b.substring(1);
                int ai = Integer.parseInt(a) - 1;
                int bi = Integer.parseInt(b) - 1;
                int ar = ai;
                int br = bi;
                int cual = 0;
                if (as == '+' && bs == '+')
                    cual = 0;
                else if (as == '+' && bs == '-') {
                    cual = 1;
                    br += n;
                } else if (as == '-' && bs == '+') {
                    cual = 2;
                    ar += n;
                } else {
                    cual = 3;
                    ar += n;
                    br += n;
                }
                if (visited[ai][bi][cual] || visited[bi][ai][cual]) continue;
                visited[ai][bi][cual] = visited[bi][ai][cual] = true;
                if (ar >= n)
                    nodes[ar - n].adjacents.add(nodes[br]);
                else
                    nodes[ar + n].adjacents.add(nodes[br]);
                if (br >= n)
                    nodes[br - n].adjacents.add(nodes[ar]);
                else
                    nodes[br + n].adjacents.add(nodes[ar]);
            }
            boolean isPossible = true;
            for (int i = 0; i < n; i++)
                if (visited[i][i][0] && visited[i][i][3]) isPossible = false;
            if (isPossible) {
                ArrayList<ArrayList<Node>> scc = SCC(nodes, dn);
                for (ArrayList<Node> a : scc) {
                    inComponent.clear();
                    for (Node node : a) {
                        int name = node.name;
                        if (name >= n) name -= n;
                        if (inComponent.contains(name)) {
                            isPossible = false;
                            break;
                        }
                        inComponent.add(name);
                    }
                    if (!isPossible) break;
                }
            }
            System.out.println(isPossible ? 1 : 0);
        }
    }
}
