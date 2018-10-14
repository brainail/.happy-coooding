/**
Given an array of integers nums and an integer k, determine whether there are 
two distinct indices i and j in the array where nums[i] = nums[j] and 
the absolute difference between i and j is less than or equal to k. 
 */

fun containsCloseNums(nums: MutableList<Int>, k: Int): Boolean {
    val recentIndexes: HashMap<Int, Int> = hashMapOf()
    nums.forEachIndexed { index, value -> 
        recentIndexes.get(value)?.let {
            if (index - it <= k) return true
        }
        recentIndexes [value] = index
    }
    return false
}
