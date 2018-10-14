/**
Given an array a that contains only numbers in the range from 1 to a.length, find the first duplicate number for which the second occurrence has the minimal index. In other words, if there are more than 1 duplicated numbers, return the number for which the second occurrence has a smaller index than the second occurrence of the other number does. If there are no such elements, return -1.

Example

For a = [2, 1, 3, 5, 3, 2], the output should be
firstDuplicate(a) = 3.

There are 2 duplicates: numbers 2 and 3. The second occurrence of 3 has a smaller index than the second occurrence of 2 does, so the answer is 3.

For a = [2, 4, 3, 5, 1], the output should be
firstDuplicate(a) = -1.

Input/Output

[execution time limit] 3 seconds (kt)

[input] array.integer a

Guaranteed constraints:
1 ≤ a.length ≤ 105,
1 ≤ a[i] ≤ a.length.

[output] integer

The element in a that occurs in the array more than once and has the minimal index for its second occurrence. If there are no such elements, return -1.
 */
fun firstDuplicate(a: MutableList<Int>): Int {
    for (value in a) {
        val valueAbs = Math.abs(value) - 1
        if (a [valueAbs] < 0) {
            return valueAbs + 1
        }
        a [valueAbs] = -a [valueAbs]
    }
    return -1
}

fun main(args: Array<String>) {
    println(firstDuplicate(mutableListOf(2, 1, 3, 5, 3, 2)) == 3)
    println(firstDuplicate(mutableListOf(2, 1, 3, 5, 4, 2)) == 2)
    println(firstDuplicate(mutableListOf(1, 2, 3, 4, 5, 4)) == 4)
}
