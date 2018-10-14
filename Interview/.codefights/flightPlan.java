class Edge {
    final int vertex;
    final int startTime;
    final int endTime;
    
    Edge(final int vertex, final int startTime, final int endTime) {
        this.vertex = vertex;
        this.startTime = startTime;
        this.endTime = endTime;
    }
}

class TimeToVertex {
    final int vertex;
    final int time;
    
    TimeToVertex(final int vertex, final int time) {
        this.vertex = vertex;
        this.time = time;
    }
}

class TimeToVertexComparator implements Comparator<TimeToVertex> {
    @Override
    public int compare(TimeToVertex tToVa, TimeToVertex tToVb) {
        if (tToVa.time < tToVb.time) {
            return -1;
        } else if (tToVa.time > tToVb.time) {
            return +1;
        } else {
            return 0;
        }
    }
}

Map<String, Integer> nameToIndex = new HashMap<>();

int getId(final String name) {
    if (!nameToIndex.containsKey(name)) {
        nameToIndex.put(name, nameToIndex.size());
    }
    return nameToIndex.get(name);
}

public static void ensureSize(List<ArrayList<Edge>> list, int size) {
    while (list.size() < size) {
        list.add(new ArrayList<>());
    }
}

List<ArrayList<Edge>> g = new ArrayList<>();

void addEdge(final int from, final int to, final int startTime, final int endTime) {
    ensureSize(g, Math.max(from, to) + 1);
    g.get(from).add(new Edge(to, startTime, endTime));
}

int parseTimeToMinutes(final String time) {
    String [] timeParts = time.split(":");
    final int hours = Integer.parseInt(timeParts [0]);
    final int minutes = Integer.parseInt(timeParts [1]);
    return hours * 60 + minutes;
}

String formatTime(final int time) {
    String hours = String.valueOf(time / 60);
    if (hours.length() < 2) hours = "0" + hours;
    String minutes = String.valueOf(time % 60);
    if (minutes.length() < 2) minutes = "0" + minutes;
    return hours + ":" + minutes;
}

String flightPlan(String[][] times, String source, String dest) {
    final int start = getId(source);
    final int finish = getId(dest);
    
    for (int u = 0; u < times.length; ++ u) {
        final int us = getId(times [u][0]);
        final int uf = getId(times [u][1]);
        final int ust = parseTimeToMinutes(times [u][2]);
        final int uft = parseTimeToMinutes(times [u][3]);
        addEdge(us, uf, ust, uft);
    }
    
    final int n = nameToIndex.size();
    final int [] timeTo = new int [n];
    Arrays.fill(timeTo, Integer.MAX_VALUE);
    timeTo [start] = -60; // we are already here, and wrrived in advance! 
    
    final PriorityQueue<TimeToVertex> queue 
        = new PriorityQueue<TimeToVertex>(n, new TimeToVertexComparator());  
    queue.add(new TimeToVertex(start, timeTo [start]));
    
    while (!queue.isEmpty()) {
        final TimeToVertex tToV = queue.remove();
        if (tToV.time > timeTo [tToV.vertex]) {
            continue; // we already have something better
        }
        
        for (final Edge edge : g.get(tToV.vertex)) {
            if (edge.startTime - tToV.time < 60) {
                continue; // no way, missed
            }
            if (edge.endTime < timeTo [edge.vertex]) {
                timeTo [edge.vertex] = edge.endTime;
                queue.add(new TimeToVertex(edge.vertex, timeTo [edge.vertex]));
            }
        }
    }
    
    return Integer.MAX_VALUE == timeTo [finish] 
        ? "-1" 
        : formatTime(timeTo [finish]);
}
