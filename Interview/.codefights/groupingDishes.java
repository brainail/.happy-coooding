String[][] groupingDishes(String[][] dishes) {
    TreeMap<String, TreeSet<String>> ings = new TreeMap<>();
    for (final String [] dishItems : dishes) {
        final String dishName = dishItems [0];
        for (int i = 1; i < dishItems.length; ++ i) {
            final String ing = dishItems [i];
            TreeSet<String> ingDishes = ings.get(ing);
            if (null == ingDishes) {
                ingDishes = new TreeSet<String>();
                ings.put(ing, ingDishes);
            }
            ingDishes.add(dishName);
        }
    }
    
    final List<String> weakIngs = new ArrayList<>();
    for (final Map.Entry<String, TreeSet<String>> entry : ings.entrySet()) {
        final String ing = entry.getKey();
        final TreeSet<String> _dishes = entry.getValue();
        if (_dishes.size() < 2) {
            weakIngs.add(ing);
        }
    }
    
    for (final String weakIng : weakIngs) {
        ings.remove(weakIng);
    }
    
    String [][] result = new String [ings.size()][];
    int row = 0;
    for (final Map.Entry<String, TreeSet<String>> entry : ings.entrySet()) {
        final String ing = entry.getKey();
        final TreeSet<String> _dishes = entry.getValue();
        result [row] = new String [_dishes.size() + 1];
        result [row][0] = ing;
        int column = 0;
        for (final String dish : _dishes) {
            result [row][++ column] = dish;
        }
        ++ row;
    }
    return result;
}
