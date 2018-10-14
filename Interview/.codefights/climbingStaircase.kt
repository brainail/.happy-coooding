fun jump(n: Int, k: Int, cur: LinkedList<Int>, all: MutableList<MutableList<Int>>) {
    if (n == 0) {
        val allItem: MutableList<Int> = mutableListOf()
        cur.forEach { value -> allItem.add(value) }
        all.add(allItem)
        return
    }
    
    for (kk in 1..minOf(n, k)) {
        cur.addLast(kk)
        jump(n - kk, k, cur, all)
        cur.removeLast()
    }
}

fun climbingStaircase(n: Int, k: Int): MutableList<MutableList<Int>> {
    val all: MutableList<MutableList<Int>> = mutableListOf()
    jump(n, k, LinkedList<Int>(), all)
    return all
}
