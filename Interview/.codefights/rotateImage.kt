/**
Note: Try to solve this task in-place (with O(1) additional memory), since this is what you'll be asked to do during an interview.

You are given an n x n 2D matrix that represents an image. Rotate the image by 90 degrees (clockwise).

Example

For

a = [[1, 2, 3],
     [4, 5, 6],
     [7, 8, 9]]
the output should be

rotateImage(a) =
    [[7, 4, 1],
     [8, 5, 2],
     [9, 6, 3]]
Input/Output

[execution time limit] 3 seconds (kt)

[input] array.array.integer a

Guaranteed constraints:
1 ≤ a.length ≤ 100,
a[i].length = a.length,
1 ≤ a[i][j] ≤ 104.
 */
fun rotateImage(matrix: MutableList<MutableList<Int>>): MutableList<MutableList<Int>> {
    val n = matrix.size
    for (angle in 0..2) {
        for (x in 0..(n shr 1)-1) {
            for (y in x..n-x-2) {
                val buffer = matrix [x][y]
                matrix [x][y] = matrix [y][n-x-1]
                matrix [y][n-x-1] = matrix [n-x-1][n-y-1]
                matrix [n-x-1][n-y-1] = matrix [n-y-1][x]
                matrix [n-y-1][x] = buffer
            }
        }
    }
    return matrix
}

fun main(args: Array<String>) {
    println(rotateImage(
        mutableListOf(
            mutableListOf(1, 2, 3),
            mutableListOf(4, 5, 6),
            mutableListOf(7, 8, 9)
        )) == mutableListOf(
            mutableListOf(7, 4, 1),
            mutableListOf(8, 5, 2),
            mutableListOf(9, 6, 3)
        ))
}
