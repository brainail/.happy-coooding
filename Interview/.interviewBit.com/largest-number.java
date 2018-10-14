public class Solution {
    // DO NOT MODIFY THE LIST
    public String largestNumber(final List<Integer> arr) {
        final int n = arr.size();
        
        // We can't modify arr, so copy them
        final List<String> sarr = new ArrayList<> (n);
        int nc = 0;
        for (final Integer x : arr) {
            final String sx = String.valueOf(x);
            sarr.add(sx);
            nc += sx.length();
        }
            
        // x + y <?> y + x
        final Comparator<String> comparator = new Comparator<String>() {
            @Override
            public int compare(String first, String second) {
                String direct = first + second;
                String inverted = second + first;
                return inverted.compareTo(direct); 
            }
        };
        
        Collections.sort(sarr, comparator);

        if ('0' == sarr.get(0).charAt(0)) {
            return "0";
        } else {
            final StringBuilder bestNumber = new StringBuilder(nc);
            for (final String sx : sarr) {
                bestNumber.append(sx);
            }
            return bestNumber.toString();   
        }
    }
}
