class DistanceToVertex {
    final int vertex;
    final int distance;
    
    DistanceToVertex(final int vertex, final int distance) {
        this.vertex = vertex;
        this.distance = distance;
    }
}

class DistanceToVertexComparator implements Comparator<DistanceToVertex> {
    @Override
    public int compare(DistanceToVertex dToVa, DistanceToVertex dToVb) {
        if (dToVa.distance < dToVb.distance) {
            return -1;
        } else if (dToVa.distance > dToVb.distance) {
            return +1;
        } else {
            return 0;
        }
    }
}

int[] graphDistances(int[][] g, int s) {
    final int [] distanceTo = new int [g.length];
    Arrays.fill(distanceTo, Integer.MAX_VALUE);
    distanceTo [s] = 0;
    
    final PriorityQueue<DistanceToVertex> queue 
        = new PriorityQueue<DistanceToVertex>(g.length, new DistanceToVertexComparator());  
    queue.add(new DistanceToVertex(s, 0));
    
    while (!queue.isEmpty()) {
        final DistanceToVertex dToV = queue.remove();
        if (dToV.distance > distanceTo [dToV.vertex]) {
            continue; // we already have something better
        }
        
        for (int toV = 0; toV < g.length; ++ toV) {
            if (g [dToV.vertex][toV] < 0) {
                continue; // no way
            }
            if (distanceTo [dToV.vertex] + g [dToV.vertex][toV] < distanceTo [toV]) {
                distanceTo [toV] = distanceTo [dToV.vertex] + g [dToV.vertex][toV];
                queue.add(new DistanceToVertex(toV, distanceTo [toV]));
            }
        }
    }
    
    return distanceTo;
}
