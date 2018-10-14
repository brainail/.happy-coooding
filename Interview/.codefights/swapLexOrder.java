/**
 * Given a string str and array of pairs that indicates which indices in 
 * the string can be swapped, return the lexicographically largest string that 
 * results from doing the allowed swaps. You can swap indices any number of times.

Example

For str = "abdc" and pairs = [[1, 4], [3, 4]], the output should be
swapLexOrder(str, pairs) = "dbca".

By swapping the given indices, you get the strings: "cbda", "cbad", "dbac", "dbca". 
The lexicographically largest string in this list is "dbca".
 */

private void connect(int i, boolean [] used, List<ArrayList<Integer>> connections, List<Integer> component) {
    if (used [i]) {
        return;
    }
    
    used [i] = true;
    component.add(i);
    
    for (final int j : connections.get(i)) {
        connect(j, used, connections, component);
    }
}

String swapLexOrder(String str, int[][] pairs) {
    final int size = str.length();
    StringBuilder result = new StringBuilder(str);
    
    List<ArrayList<Integer>> connections = new ArrayList<>(size);
    for (int i = 0; i < size; ++ i) {
        connections.add(new ArrayList<Integer>());
    }
    for (final int [] pair : pairs) {
        connections.get(pair [0] - 1).add(pair [1] - 1);
        connections.get(pair [1] - 1).add(pair [0] - 1);
    }
    
    boolean [] used = new boolean [size];
    for (int i = 0; i < size; ++ i) {
        if (used [i]) { 
            continue;
        }
        
        final List<Integer> component = new ArrayList<>();
        connect(i, used, connections, component);
        
        char [] componentChars = new char [component.size()];
        for (int q = 0; q < componentChars.length; ++ q) {
            componentChars [q] = str.charAt(component.get(q));
        }
        
        Collections.sort(component);
        Arrays.sort(componentChars);

        for (int q = 0; q < componentChars.length; ++ q) {
            result.setCharAt(component.get(q), componentChars [componentChars.length - q - 1]);
        }
    }
    
    return result.toString();
}
