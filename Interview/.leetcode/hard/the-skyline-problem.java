/**
 * A city's skyline is the outer contour of the silhouette formed by all the
 * buildings in that city when viewed from a distance. Now suppose you are given
 * the locations and height of all the buildings as shown on a cityscape photo
 * (Figure A), write a program to output the skyline formed by these buildings
 * collectively (Figure B).
 */
class Solution {
    static class Column {
        static final Column EMPTY = new Column(Integer.MAX_VALUE, Integer.MAX_VALUE, 0);

        private final int index;
        final int position;
        final int height;

        Column(int index, int position, int height) {
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

    static class ColumnsHeightComparator implements Comparator<Column> {
        public int compare(Column first, Column second) {
            return -Integer.compare(first.height, second.height);
        }
    }

    static class ColumnsPositionComparator implements Comparator<Column> {
        public int compare(Column first, Column second) {
            final int pc = Integer.compare(first.position, second.position);
            final int ic = Integer.compare(first.signIndex(), second.signIndex());
            if (0 == pc) {
                return 0 == ic ? -first.signIndex() * Integer.compare(first.height, second.height) : -ic;
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
            if (!isColumnUsed[column.normIndex()])
                return column;
            columnsQueue.remove();
        }
        return Column.EMPTY;
    }

    void checkSkyscraperWith(final Column column) {
        final Column skyscraper = getSkyscraper();
        if (column.height > skyscraper.height) {
            int height = column.signIndex() < 0 ? skyscraper.height : column.height;
            skyline.add(new Column(column.index, column.position, height));
        }
    }

    List<int[]> getSkyline(final int[][] buildings) {
        final int n = buildings.length;
        columnsQueue = new PriorityQueue<>(n + 1, new ColumnsHeightComparator());
        allColumns = new Column[n * 2];
        isColumnUsed = new boolean[n];

        for (int i = 0; i < n; ++i) {
            allColumns[i * 2] = new Column((i + 1), buildings[i][0], buildings[i][2]);
            allColumns[i * 2 + 1] = new Column(-(i + 1), buildings[i][1], buildings[i][2]);
        }
        Arrays.sort(allColumns, new ColumnsPositionComparator());

        skyline = new ArrayList<>(n);
        for (final Column column : allColumns) {
            if (column.signIndex() < 0)
                isColumnUsed[column.normIndex()] = true;
            checkSkyscraperWith(column);
            if (column.signIndex() > 0)
                columnsQueue.add(column);
        }

        final List<int[]> skylineResult = new ArrayList<>(skyline.size());
        for (int i = 0; i < skyline.size(); ++i) {
            skylineResult.add(new int[] { skyline.get(i).position, skyline.get(i).height });
        }
        return skylineResult;
    }
}
