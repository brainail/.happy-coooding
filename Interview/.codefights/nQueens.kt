fun placement(
    column: Int, n: Int, 
    indexes: MutableList<Int>, 
    firstDiag: MutableSet<Int>,
    secondDiag: MutableSet<Int>,
    rows: MutableSet<Int>,
    all: MutableList<MutableList<Int>>) {
    
    if (column == n) {
        all.add(indexes.toMutableList())
        return
    }
    
    for (row in 0..n-1) {
        if (firstDiag.contains(row - column)) continue
        if (secondDiag.contains(row + column)) continue
        if (rows.contains(row)) continue
        indexes [column] = row + 1
        firstDiag += (row - column) 
        secondDiag += (row + column) 
        rows += row
        placement(column + 1, n, indexes, firstDiag, secondDiag, rows, all)
        indexes [column] = -1
        firstDiag -= (row - column) 
        secondDiag -= (row + column) 
        rows -= row
    }
}

fun nQueens(n: Int): MutableList<MutableList<Int>> {
    val result: MutableList<MutableList<Int>> = mutableListOf()
    val indexes = MutableList(n, { -1 }) 
    placement(0, n, indexes, mutableSetOf(), mutableSetOf(), mutableSetOf(), result)
    return result
}
