//
//data class Tree<T>(var value: T) {
//    var left: Tree<T>? = null;
//    var right: Tree<T>? = null;
//}

fun treeSum(t: Tree<Int>?, curNumber: Long = 0): Long {
    if (null == t?.left && null == t?.right) return curNumber
    var sum: Long = 0
    val leftNode = t?.left
    sum += if (null != leftNode) treeSum(leftNode, curNumber * 10 + leftNode.value) else 0
    val rightNode = t?.right
    sum += if (null != rightNode) treeSum(rightNode, curNumber * 10 + rightNode.value) else 0
    return sum
}

fun digitTreeSum(t: Tree<Int>?): Long {
    return treeSum(t, (t?.value ?: 0).toLong())
}
