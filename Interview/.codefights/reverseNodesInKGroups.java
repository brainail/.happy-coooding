/**
 * Note: Your solution should have O(n) time complexity, where n is the number
 * of element in l, and O(1) additional space complexity, since this is what you
 * would be asked to accomplish in an interview.
 * 
 * Given a linked list l, reverse its nodes k at a time and return the modified
 * list. k is a positive integer that is less than or equal to the length of l.
 * If the number of nodes in the linked list is not a multiple of k, then the
 * nodes that are left out at the end should remain as-is.
 * 
 * You may not alter the values in the nodes - only the nodes themselves can be
 * changed.
 * 
 * Example
 * 
 * For l = [1, 2, 3, 4, 5] and k = 2, the output should be
 * reverseNodesInKGroups(l, k) = [2, 1, 4, 3, 5]; For l = [1, 2, 3, 4, 5] and k
 * = 1, the output should be reverseNodesInKGroups(l, k) = [1, 2, 3, 4, 5]; For
 * l = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11] and k = 3, the output should be
 * reverseNodesInKGroups(l, k) = [3, 2, 1, 6, 5, 4, 9, 8, 7, 10, 11].
 * Input/Output
 * 
 * [execution time limit] 3 seconds (java)
 * 
 * [input] linkedlist.integer l
 * 
 * A singly linked list of integers.
 * 
 * Guaranteed constraints: 1 ≤ list size ≤ 104, -109 ≤ element value ≤ 109.
 * 
 * [input] integer k
 * 
 * The size of the groups of nodes that need to be reversed.
 * 
 * Guaranteed constraints: 1 ≤ k ≤ l size.
 * 
 * [output] linkedlist.integer
 * 
 * The initial list, with reversed groups of k elements.
 */

// Definition for singly-linked list:
class ListNode<T> {
  ListNode(T x) {
    value = x;
  }
  T value;
  ListNode<T> next;
}

static class Split {
    public final ListNode<Integer> from;
    public final ListNode<Integer> to;
    public final ListNode<Integer> next;
    
    public Split(
        final ListNode<Integer> from, 
        final ListNode<Integer> to, 
        final ListNode<Integer> next) {
        
        this.from = from;
        this.to = to;
        this.next = next;
    }
}

Split reverse(ListNode<Integer> from, int k) {
    ListNode<Integer> prev = null;
    ListNode<Integer> current = from;
    boolean enough = true;
    
    for (int i = 0; i < k; ++ i) {
        if (null == current) {
            enough = false;
            break;
        } else {
            prev = current;
            current = null != current ? current.next : null;
        }
    }
    
    if (!enough) {
        return new Split(from, prev, null);
    }
    
    prev = null;
    current = from;
    ListNode<Integer> next = null;
    while (current != null && k-- > 0) {
        next = current.next;
        current.next = prev;
        prev = current;
        current = next;
    }
    
    return new Split(prev, from, current);
}

ListNode<Integer> reverseNodesInKGroups(ListNode<Integer> l, int k) {
    ListNode<Integer> head = new ListNode(0);
    ListNode<Integer> cur = head;
    while (null != l) {
        Split split = reverse(l, k);
        cur.next = split.from;
        cur = split.to;
        l = split.next;
    }
    return head.next;
}
