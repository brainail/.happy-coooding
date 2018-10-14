static class Column {
    static final Column EMPTY = new Column(Integer.MAX_VALUE, Integer.MAX_VALUE, 0);

    private final int index;
    final double position;
    final double height;

    Column(int index, double position, double height) {
        this.index = index;
        this.position = position;
        this.height = height;
    }

    int normIndex() {
        return Math.abs(index) - 1;
    }

    int signIndex() {
        return index < 0 ? -1 : +1;
    }
}

class ColumnsHeightComparator implements Comparator<Column> {
    public int compare(Column first, Column second) {
        return -Double.compare(first.height, second.height);
    }
}

class ColumnsPositionComparator implements Comparator<Column> {
    public int compare(Column first, Column second) {
        final int pc = Double.compare(first.position, second.position);
        final int ic = Double.compare(first.signIndex(), second.signIndex());
        if (0 == pc) {
            return 0 == ic ? -first.signIndex() * Double.compare(first.height, second.height) : -ic;
        } else {
            return pc;
        }
    }
}

    Column[] allColumns;
    boolean[] isColumnUsed;
    PriorityQueue<Column> columnsQueue;
    List<Column> skyline;

    Column getSkyscraper() {
        while (!columnsQueue.isEmpty()) {
            Column column = columnsQueue.peek();
            if (!isColumnUsed[column.normIndex()]) return column;
            columnsQueue.remove();
        }
        return Column.EMPTY;
    }

    void checkSkyscraperWith(final Column column) {
        final Column skyscraper = getSkyscraper();
        if (column.height > skyscraper.height) {
            double height = column.signIndex() < 0 ? skyscraper.height : column.height;
            skyline.add(new Column(column.index, column.position, height));
        }
    }

double [][] getSkyline(final double [][] buildings) {
    final int n = buildings.length;
    columnsQueue = new PriorityQueue<>(n, new ColumnsHeightComparator()); 
    allColumns = new Column [n * 2];
    isColumnUsed = new boolean [n];
    
    for (int i = 0; i < n; ++ i) {
        allColumns [i * 2] = new Column(
            (i + 1), buildings [i][0], buildings [i][2]);
        allColumns [i * 2 + 1] = new Column(
            -(i + 1), buildings [i][0] + buildings [i][1], buildings [i][2]);
    }
    Arrays.sort(allColumns, new ColumnsPositionComparator());
    
    skyline = new ArrayList<>(n);
    for (final Column column : allColumns) {
        if (column.signIndex() < 0) isColumnUsed [column.normIndex()] = true;
        checkSkyscraperWith(column);
        if (column.signIndex() > 0) columnsQueue.add(column);
    }
    
    final double [][] skylineResult = new double [skyline.size()][];
    for (int i = 0; i < skylineResult.length; ++ i) {
        final Column column = skyline.get(i);
        skylineResult [i] = new double [2];
        skylineResult [i][0] = column.position;
        skylineResult [i][1] = column.height;
    }
    
    return skylineResult;
}
