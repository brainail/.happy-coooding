/**
You have a collection of coins, and you know the values of the coins 
and the quantity of each type of coin in it. You want to know how many 
distinct sums you can make from non-empty groupings of these coins.

Example

For coins = [10, 50, 100] and quantity = [1, 2, 1], the output should be
possibleSums(coins, quantity) = 9.

Here are all the possible sums:

50 = 50;
10 + 50 = 60;
50 + 100 = 150;
10 + 50 + 100 = 160;
50 + 50 = 100;
10 + 50 + 50 = 110;
50 + 50 + 100 = 200;
10 + 50 + 50 + 100 = 210;
10 = 10;
100 = 100;
10 + 100 = 110.
 */

fun possibleSums(coins: MutableList<Int>, quantity: MutableList<Int>): Int {
   var memo: HashSet<Long> = hashSetOf()
   val queue : Deque<Triple<Int, Int, Long>> = LinkedList()
   queue.addFirst(Triple(0, 0, 0))
   while (!queue.isEmpty()) {
      val (i, q, s) = queue.removeFirst()
      if (i == coins.size) {
         memo.add(s)
      } else {
         queue.addLast(Triple(i + 1, 0, s))
         if (q + 1 <= quantity [i]) {
            queue.addLast(Triple(i, q + 1, s + coins [i]))
         }
      }
   }
   return memo.size - 1
}
