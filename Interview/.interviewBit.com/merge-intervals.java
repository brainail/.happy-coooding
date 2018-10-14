/**
 * Definition for an interval.
 * public class Interval {
 *     int start;
 *     int end;
 *     Interval() { start = 0; end = 0; }
 *     Interval(int s, int e) { start = s; end = e; }
 * }
 */
public class Solution {
    public ArrayList<Interval> insert(ArrayList<Interval> intervals, Interval newInterval) {
        final ArrayList<Interval> result = new ArrayList<>();
        
        int mergeStart = newInterval.start;
        int mergeEnd = newInterval.end;
        boolean merged = false;
        
        for (int i = 0; i < intervals.size(); ++ i) {
            final Interval currentInterval = intervals.get(i);
            
            // #1
            if (currentInterval.end < newInterval.start) {
                result.add(currentInterval);
                continue;
            }
            
            // #2
            if (currentInterval.start > newInterval.end) {
                // #2.1
                if (!merged) {
                    result.add(new Interval(mergeStart, mergeEnd));
                    merged = true;
                }
                result.add(currentInterval);
                continue;
            }
                    
            // #3.1
            if (currentInterval.start <= newInterval.start) {
                mergeStart = currentInterval.start;
            }
            // #3.2
            if (currentInterval.end >= newInterval.end) {
                mergeEnd = currentInterval.end;
            }
        }
        
        // #4
        if (!merged) {
            result.add(new Interval(mergeStart, mergeEnd));
        }
        
        return result;
    }
}
