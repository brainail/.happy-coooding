package utilities.graph;

import java.util.*;

/**
 * determines if a graph is two colorable
 */
public class TwoColouring
{
    enum Color {
        UNKNOWN, BLACK, WHITE
    };

    public static Color[] color;
    public static int[][] adjacencyMatrix;
    public static boolean possible;

    public static void main(String[] args)
    {
        int numNodes = 9;
        adjacencyMatrix = new int[numNodes][numNodes];

        // adjacencyMatrix[0][1] = 1;
        // adjacencyMatrix[1][2] = 1;
        // adjacencyMatrix[2][0] = 1;

        for (int i = 1; i <= 8; i++) {
            adjacencyMatrix[0][i] = 1;
        }

        for (int i = 0; i < adjacencyMatrix.length; i++) {
            // System.out.println(Arrays.toString(adjacencyMatrix[i]));
        }

        possible = true;
        color = new Color[numNodes];

        for (int V = 0; V < color.length; V++) {
            color[V] = Color.UNKNOWN;
        }

        for (int V = 0; V < color.length; V++) {
            if (color[V].equals(Color.UNKNOWN)) {
                colorify(V, Color.BLACK, Color.WHITE);
            }
        }

        System.out.println(Arrays.toString(color));
        if (possible)
            System.out.println("POSSIBLE.");
        else
            System.out.println("NOT POSSIBLE.");
    }

    /**
     * do a DFS on the graph, coloring alternating black and white nodes.
     * If a conflict is found, then the graph is not 2-colorable, and
     * the scheduling is impossible.
     * 
     * @param V
     * @param C1
     * @param C2
     */
    public static void colorify(int V, Color C1, Color C2)
    {
        color[V] = C1;
        for (int V2 = 0; V2 < adjacencyMatrix[0].length; V2++) {
            if (adjacencyMatrix[V][V2] > 0) {
                if (color[V2].equals(C1)) {
                    possible = false;
                    return;
                }
                if (color[V2].equals(Color.UNKNOWN)) {
                    colorify(V2, C2, C1);
                }
            }
        }
    }
}