fun findLongestSubarrayBySum(s: Int, arr: MutableList<Int>): MutableList<Int> {
    var curSum = 0
    var curRight = -1
    var bounds = mutableListOf(-1)
    arr.forEachIndexed { index, value ->
        if (curRight < index) {
            curRight = index
            curSum = value
        }
        while (curRight + 1 < arr.size && curSum + arr [curRight + 1] <= s) {
            curSum += arr [++ curRight]
        }
        if (s == curSum) {
            if (bounds [0] < 0 || curRight - index > bounds [1] - bounds [0]) {
                bounds = mutableListOf(index + 1, curRight + 1)
            }
        }
        curSum -= value
    }
    return bounds
}
