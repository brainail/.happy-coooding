/**
 * Given N axis-aligned rectangles where N > 0, determine if they all together
 * form an exact cover of a rectangular region.
 * 
 * Each rectangle is represented as a bottom-left point and a top-right point.
 * For example, a unit square is represented as [1,1,2,2]. (coordinate of
 * bottom-left point is (1, 1) and top-right point is (2, 2)).
 */

// based on the fact that corners should be even (except the outer ones)
class Solution {
    public boolean isRectangleCover(int[][] rectangles) {
        if (rectangles.length == 0 || rectangles[0].length == 0) return false;

        int x1 = Integer.MAX_VALUE, x2 = Integer.MIN_VALUE;
        int y1 = Integer.MAX_VALUE, y2 = Integer.MIN_VALUE;

        HashSet<String> set = new HashSet<String>();
        int area = 0;

        for (int[] rect : rectangles) {
            x1 = Math.min(rect[0], x1);
            y1 = Math.min(rect[1], y1);
            x2 = Math.max(rect[2], x2);
            y2 = Math.max(rect[3], y2);

            area += (rect[2] - rect[0]) * (rect[3] - rect[1]);

            if (!set.add(rect[0] + " " + rect[1])) set.remove(rect[0] + " " + rect[1]);
            if (!set.add(rect[0] + " " + rect[3])) set.remove(rect[0] + " " + rect[3]);
            if (!set.add(rect[2] + " " + rect[3])) set.remove(rect[2] + " " + rect[3]);
            if (!set.add(rect[2] + " " + rect[1])) set.remove(rect[2] + " " + rect[1]);
        }

        if (!set.contains(x1 + " " + y1) || !set.contains(x1 + " " + y2) 
                || !set.contains(x2 + " " + y1) || !set.contains(x2 + " " + y2)) return false;

        return set.size() == 4 && area == (x2 - x1) * (y2 - y1);
    }
}

// sweep lnes solution
class Solution {
    public class Event implements Comparable<Event> {
        int time;
        int[] rect;

        public Event(int time, int[] rect) {
            this.time = time;
            this.rect = rect;
        }

        public int compareTo(Event that) {
            return time != that.time ? time - that.time : rect[0] - that.rect[0];
        }
    }

    public boolean isRectangleCover(int[][] rectangles) {
        PriorityQueue<Event> pq = new PriorityQueue<Event>();
        int[] border = { Integer.MAX_VALUE, Integer.MIN_VALUE };
        for (int[] rect : rectangles) {
            for (int t = 0; t <= 2; t += 2)
                pq.add(new Event(rect[t], rect));
            if (rect[1] < border[0])
                border[0] = rect[1];
            if (rect[3] > border[1])
                border[1] = rect[3];
        }
        final TreeSet<int[]> set = new TreeSet<int[]>(new Comparator<int[]>() {
            @Override
            public int compare(int[] rect1, int[] rect2) {
                // 0 will allow us determine during adding if there is intersection
                return rect1[3] <= rect2[1] ? -1 : (rect2[3] <= rect1[1] ? 1 : 0);
            }
        });
        int totalY = 0;
        while (!pq.isEmpty()) {
            int time = pq.peek().time;
            while (!pq.isEmpty() && pq.peek().time == time) { // while the same vertical line
                Event e = pq.poll();
                if (time == e.rect[2]) { // end
                    set.remove(e.rect);
                    totalY -= e.rect[3] - e.rect[1];
                } else { // start
                    if (!set.add(e.rect))
                        return false;
                    totalY += e.rect[3] - e.rect[1];
                }
            }
            if (!pq.isEmpty() && totalY != border[1] - border[0])
                return false;
        }
        return true;
    }
}