/**
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 * 
 * Example 1:
 * 
 * Input: 1->2->3->3->4->4->5 Output: 1->2->5 Example 2:
 * 
 * Input: 1->1->1->2->3 Output: 2->3
 */

class Solution {
    public ListNode deleteDuplicates(ListNode head) {
        if (null == head || head.next == null)
            return head;
        ListNode cur = head;
        head = new ListNode(-1);
        ListNode tail = head;
        while (null != cur) {
            ListNode last = cur;
            int count = 0;
            while (null != last && last.val == cur.val) {
                ++count;
                last = last.next;
            }
            if (count == 1) {
                tail.next = cur;
                tail = cur;
            }
            cur = last;
        }
        tail.next = null;
        return head.next;
    }
}
