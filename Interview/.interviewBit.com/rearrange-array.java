public class Solution {
    public int pack(final int X, final int Y) {
        return (Y << 16) | (X & 0xFFFF);
    }

    public int sunpackY(final int Z) {
        return Z >> 16; 
    }

    public int sunpackX(final int Z) {
        return (short) (Z & 0xFFFF);
    }
    
    public int unpackY(final int Z) {
        return Z >>> 16; 
    }

    public int unpackX(final int Z) {
        return Z & 0xFFFF;
    }

    public void arrange(final ArrayList<Integer> arr) {
        final int n = arr.size();
        for (int i = 0; i < n; ++ i) {
            final int next = arr.get(arr.get(i));
            if (0 == unpackY(next)) {
                arr.set(i, pack(arr.get(i), next + 1));
            } else {
                arr.set(i, pack(arr.get(i), unpackX(next) + 1));
            }
        }
        for (int i = 0; i < n; ++ i) {
            arr.set(i, unpackY(arr.get(i)) - 1);
        }
    }
}
