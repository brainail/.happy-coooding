/**
 * Sort a linked list in O(n log n) time using constant space complexity.
 * 
 * Example 1:
 * 
 * Input: 4->2->1->3 Output: 1->2->3->4 Example 2:
 * 
 * Input: -1->5->3->4->0 Output: -1->0->3->4->5
 */

class Solution {
    public ListNode sortList(ListNode head) {
        boolean changed = true;
        for (int count = 1; changed; count <<= 1) {
            changed = false;
            ListNode first = head, second, prev = new ListNode(-1);
            head = prev;
            while (null != first) {
                second = first;
                for (int i = 0; i < count && null != second; ++i) second = second.next;
                if (null != second) changed = true;
                for (int ia = 0, ib = 0; (ia < count || ib < count) && (null != first || null != second);) {
                    if (ia < count && (ib == count || null == second || first.val < second.val)) {
                        prev.next = first;
                        first = first.next;
                        ++ia;
                    } else if (null != second) {
                        prev.next = second;
                        second = second.next;
                        ++ib;
                    } else {
                        break;
                    }
                    prev = prev.next;
                }
                first = second;
            }
            prev.next = null; // remove obsolette possible cycle
            head = head.next;
        }
        return head;
    }
}
