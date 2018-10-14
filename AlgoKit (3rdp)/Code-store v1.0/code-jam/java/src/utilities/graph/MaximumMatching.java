package utilities.graph;

import java.util.*;

/**
 * An engine for finding the maximum-weight matching in a complete bipartite
 * graph. Suppose we have two sets <i>S</i> and <i>T</i>, both of size <i>n</i>.
 * For each <i>i</i> in <i>S</i> and <i>j</i> in <i>T</i>, we have a weight
 * <i>w<sub>ij</sub></i>. A perfect matching <i>X</i> is a subset of <i>S</i> x
 * <i>T</i> such that each <i>i</i> in <i>S</i> occurs in exactly one element of
 * <i>X</i>, and each <i>j</i> in <i>T</i> occurs in exactly one element of
 * <i>X</i>. Thus, <i>X</i> can be thought of as a one-to-one function from
 * <i>S</i> to <i>T</i>. The weight of <i>X</i> is the sum, over (<i>i</i>,
 * <i>j</i>) in <i>X</i>, of <i>w<sub>ij</sub></i>. A BipartiteMatcher takes the
 * number <i>n</i> and the weights <i>w<sub>ij</sub></i>, and finds a perfect
 * matching of maximum weight.
 * 
 * It uses the Hungarian algorithm of Kuhn (1955), as improved and presented by
 * E. L. Lawler in his book <cite>Combinatorial Optimization: Networks and
 * Matroids</cite> (Holt, Rinehart and Winston, 1976, p. 205-206). The running
 * time is O(<i>n</i><sup>3</sup>). The weights can be any finite real numbers;
 * Lawler's algorithm assumes positive weights, so if necessary we add a
 * constant <i>c</i> to all the weights before running the algorithm. This
 * increases the weight of every perfect matching by <i>nc</i>, which doesn't
 * change which perfect matchings have maximum weight.
 * 
 * If a weight is set to Double.NEGATIVE_INFINITY, then the algorithm will
 * behave as if that edge were not in the graph. If all the edges incident on a
 * given node have weight Double.NEGATIVE_INFINITY, then the final result will
 * not be a perfect matching, and an exception will be thrown.
 * 
 */
/* Sample usage */
// BipartiteMatcher matcher = new BipartiteMatcher();
// int N = 8; // num nodes on each side
// matcher.init(N, Double.NEGATIVE_INFINITY);
//
// /* DEBUG */
// matcher.printWeights();
// int[] matching = matcher.getMatching();
// System.out.println("Maximum-weight matching:");
// for (int i = 0; i < n; i++) {
// System.out.println(i + ": " + matching[i]);
// }
public class MaximumMatching
{
    /**
     * Tolerance for comparisons to zero, to account for floating-point
     * imprecision. We consider a positive number to be essentially zero if it
     * is strictly less than TOL.
     */
    public static final double TOL = 1e-10;
    public static final int NO_LABEL = -1, EMPTY_LABEL = -2;
    public int n;
    public double[][] weights;
    public double minWeight, maxWeight;
    // If (i, j) is in the mapping, then sMatches[i] = j and tMatches[j] = i.
    // If i is unmatched, then sMatches[i] = -1 (and likewise for tMatches).
    public int[] sMatches, tMatches, sLabels, tLabels;
    public double[] u, v, pi;
    public List<Integer> eligibleS = new ArrayList<Integer>(),
                    eligibleT = new ArrayList<Integer>();

    /**
     * Creates a BipartiteMatcher without specifying the graph size. Calling any
     * other method before calling reset will yield an IllegalStateException.
     */
    public MaximumMatching()
    {
        n = -1;
    }

    /**
     * Creates a BipartiteMatcher and prepares it to run on an n x n graph. All
     * the weights are initially set to 1.
     */
    public MaximumMatching(int n)
    {
        init(n);
    }

    /**
     * <code>initialWeight</code> defaults to {@link Integer#1}.
     * 
     * @see MaximumMatching#init(int, double)
     */
    public void init(int n)
    {
        init(n, 1);
    }

    /**
     * Resets the BipartiteMatcher to run on an n x n graph. The weights are all
     * initialised to <code>initialWeight</code>.
     */
    public void init(int n, double initialWeight)
    {
        if (n < 0) {
            throw new IllegalArgumentException("Negative num nodes: " + n);
        }
        this.n = n;

        weights = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                weights[i][j] = initialWeight;
            }
        }
        minWeight = 1;
        maxWeight = Double.NEGATIVE_INFINITY;

        sMatches = new int[n];
        tMatches = new int[n];
        sLabels = new int[n];
        tLabels = new int[n];
        u = new double[n];
        v = new double[n];
        pi = new double[n];
    }

    /**
     * Sets the weight w<sub>ij</sub> to the given value w.
     * 
     * @throws IllegalArgumentException if i or j is outside the range [0, n).
     */
    public void setWeight(int i, int j, double w)
    {
        if (n == -1) {
            throw new IllegalStateException("Graph size not specified.");
        }
        if ((i < 0) || (i >= n)) {
            throw new IllegalArgumentException("i-value out of range: " + i);
        }
        if ((j < 0) || (j >= n)) {
            throw new IllegalArgumentException("j-value out of range: " + j);
        }
        if (Double.isNaN(w)) {
            throw new IllegalArgumentException("Illegal weight: " + w);
        }

        weights[i][j] = w;
        if ((w > Double.NEGATIVE_INFINITY) && (w < minWeight)) {
            minWeight = w;
        }
        if (w > maxWeight) {
            maxWeight = w;
        }
    }

    /**
     * Returns a maximum-weight perfect matching relative to the weights
     * specified with setWeight. The matching is represented as an array arr of
     * length n, where arr[i] = j if (i,j) is in the matching.
     * 
     * ('-1' represents 'no matching found')
     */
    public int[] getMatching()
    {
        if (n == -1) {
            throw new IllegalStateException("Graph size not specified.");
        }
        if (n == 0) {
            return new int[0];
        }
        ensurePositiveWeights();

        // Step 0: Initialization
        eligibleS.clear();
        eligibleT.clear();
        for (int i = 0; i < n; i++) {
            sMatches[i] = -1;
            tMatches[i] = -1;

            u[i] = maxWeight; // ambiguous on p. 205 of Lawler, but see p. 202
            v[i] = 0;
            pi[i] = Double.POSITIVE_INFINITY;

            // this is really first run of Step 1.0
            sLabels[i] = EMPTY_LABEL;
            eligibleS.add(new Integer(i));

            tLabels[i] = NO_LABEL;
        }

        while (true) {
            // Augment the matching until we can't augment any more given the
            // current settings of the dual variables.
            while (true) {
                // Steps 1.1-1.4: Find an augmenting path
                int lastNode = findAugmentingPath();
                if (lastNode == -1) {
                    break; // no augmenting path
                }

                // Step 2: Augmentation
                flipPath(lastNode);
                for (int i = 0; i < n; i++) {
                    pi[i] = Double.POSITIVE_INFINITY;
                    sLabels[i] = NO_LABEL;
                    tLabels[i] = NO_LABEL;
                }

                // This is Step 1.0
                eligibleS.clear();
                for (int i = 0; i < n; i++) {
                    if (sMatches[i] == -1) {
                        sLabels[i] = EMPTY_LABEL;
                        eligibleS.add(new Integer(i));
                    }
                }

                eligibleT.clear();
            }

            // Step 3: Change the dual variables

            // delta1 = min_i u[i]
            double delta1 = Double.POSITIVE_INFINITY;
            for (int i = 0; i < n; i++) {
                if (u[i] < delta1) {
                    delta1 = u[i];
                }
            }

            // delta2 = min_{j : pi[j] > 0} pi[j]
            double delta2 = Double.POSITIVE_INFINITY;
            for (int j = 0; j < n; j++) {
                if ((pi[j] >= TOL) && (pi[j] < delta2)) {
                    delta2 = pi[j];
                }
            }

            if (delta1 < delta2) {
                // In order to make another pi[j] equal 0, we'd need to
                // make some u[i] negative.
                break; // we have a maximum-weight matching
            }

            changeDualVars(delta2);
        }

        int[] matching = new int[n];
        for (int i = 0; i < n; i++) {
            matching[i] = sMatches[i];
        }
        return matching;
    }

    /**
     * Tries to find an augmenting path containing only edges (i,j) for which
     * u[i] + v[j] = weights[i][j]. If it succeeds, returns the index of the
     * last node in the path. Otherwise, returns -1. In any case, updates the
     * labels and pi values.
     */
    public int findAugmentingPath()
    {
        while ((!eligibleS.isEmpty()) || (!eligibleT.isEmpty())) {
            if (!eligibleS.isEmpty()) {
                int i = (eligibleS.get(eligibleS.size() - 1)).intValue();
                eligibleS.remove(eligibleS.size() - 1);
                for (int j = 0; j < n; j++) {
                    // If pi[j] has already been decreased essentially
                    // to zero, then j is already labeled, and we
                    // can't decrease pi[j] any more. Omitting the
                    // pi[j] >= TOL check could lead us to relabel j
                    // unnecessarily, since the diff we compute on the
                    // next line may end up being less than pi[j] due
                    // to floating point imprecision.
                    if ((tMatches[j] != i) && (pi[j] >= TOL)) {
                        double diff = u[i] + v[j] - weights[i][j];
                        if (diff < pi[j]) {
                            tLabels[j] = i;
                            pi[j] = diff;
                            if (pi[j] < TOL) {
                                eligibleT.add(new Integer(j));
                            }
                        }
                    }
                }
            } else {
                int j = (eligibleT.get(eligibleT.size() - 1)).intValue();
                eligibleT.remove(eligibleT.size() - 1);
                if (tMatches[j] == -1) {
                    return j; // we've found an augmenting path
                }

                int i = tMatches[j];
                sLabels[i] = j;
                eligibleS.add(new Integer(i)); // ok to add twice
            }
        }

        return -1;
    }

    /**
     * Given an augmenting path ending at lastNode, "flips" the path. This means
     * that an edge on the path is in the matching after the flip if and only if
     * it was not in the matching before the flip. An augmenting path connects
     * two unmatched nodes, so the result is still a matching.
     */
    public void flipPath(int lastNode)
    {
        while (lastNode != EMPTY_LABEL) {
            int parent = tLabels[lastNode];

            // Add (parent, lastNode) to matching. We don't need to
            // explicitly remove any edges from the matching because:
            // * We know at this point that there is no i such that
            // sMatches[i] = lastNode.
            // * Although there might be some j such that tMatches[j] =
            // parent, that j must be sLabels[parent], and will change
            // tMatches[j] in the next time through this loop.
            sMatches[parent] = lastNode;
            tMatches[lastNode] = parent;

            lastNode = sLabels[parent];
        }
    }

    public void changeDualVars(double delta)
    {
        for (int i = 0; i < n; i++) {
            if (sLabels[i] != NO_LABEL) {
                u[i] -= delta;
            }
        }

        for (int j = 0; j < n; j++) {
            if (pi[j] < TOL) {
                v[j] += delta;
            } else if (tLabels[j] != NO_LABEL) {
                pi[j] -= delta;
                if (pi[j] < TOL) {
                    eligibleT.add(new Integer(j));
                }
            }
        }
    }

    /**
     * Ensures that all weights are either Double.NEGATIVE_INFINITY, or strictly
     * greater than zero.
     */
    private void ensurePositiveWeights()
    {
        // minWeight is the minimum non-infinite weight
        if (minWeight < TOL) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    weights[i][j] = weights[i][j] - minWeight + 1;
                }
            }

            maxWeight = maxWeight - minWeight + 1;
            minWeight = 1;
        }
    }

    /**
     * DEBUG: prints 2D array of weights as initialised
     */
    public void printWeights()
    {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(weights[i][j] + " ");
            }
            System.out.println("");
        }
    }

    /**
     * DEBUG: prints out final assignments, according to matching[] array
     * 
     * @param matching
     */
    public void printMatchings(int[] matching)
    {
        for (int i = 0; i < n; i++) {
            System.out.println(i + ": " + matching[i]);
        }
    }
}
