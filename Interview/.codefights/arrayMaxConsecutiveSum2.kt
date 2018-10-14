fun arrayMaxConsecutiveSum2(inputArray: MutableList<Int>): Int {
    var sum = 0
    var max = Int.MIN_VALUE
    inputArray.forEach {
        sum += it
        max = maxOf(max, sum)
        sum = maxOf(sum, 0)
    }
    return max
}
